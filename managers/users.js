//
// Libraries used in this manager
const UsersAdapter = require('../adapters/users');
const sha256 = require('../libs/sha256');

initAdminUser();

//
// Create admin if not exists
function initAdminUser() {
  return UsersAdapter.findByName('admin')
  .then(function (user) {
    if (!user) {
      UsersAdapter.createUser('admin', 'admin@example.com', sha256('admin'));
    }
  });
}

function checkNewUserName(name) {
  return (!name || !name.length ? 'Empty user name' : null);
}

function checkNewUserEmail(email) {
  return (!email || !email.length ? 'Invalid user email' : null);
}

function checkNewUserPassword(password, confirmation) {
  return (!password || !confirmation || !password.length ? 'Invalid user password/confirmation' : null);
}

function checkNewUserValues(name, email, password, confirmation) {
  var error = null;

  if ((error = checkNewUserName(name)) || (error = checkNewUserEmail(email)) ||
  (error = checkNewUserPassword(password, confirmation))) {
    return error;
  }

  return null;
}

function checkAndCreateUser(name, email, password, confirmation) {
  return new Promise(function (fulfill, reject) {
    const error = checkNewUserValues(name, email, password, confirmation);

    if (error) {
      reject(error);
    }

    UsersAdapter.findByEmail(email)
    .then(function (user) {
      if (!user) {
        UsersAdapter.findByName(name)
        .then(function (user) {
          if (!user) {
            UsersAdapter.createUser(name, email, sha256(password))
            .then(function (user) {
              fulfill(user);
            }).catch(function (error) {
              reject(error);
            });
          } else {
            reject('A user already exists with this name ' + name);
          }
        });
      } else {
        reject('A user already exists with this email ' + email);
      }
    });
  });
}

//
// Create user entry point from its POST route
module.exports.createUser = function (params) {
  return function (req, res) {
    checkAndCreateUser(req.body.username, req.body.email, req.body.password, req.body.confirmation)
      .then(function (user) {
        req.session.save(function () {
          res.redirect(params.successRedirect);
        });
      }).catch(function (error) {
        res.redirect(params.failureRedirect);
      }
    );
  };
};

//
// User identification for passport library
module.exports.identifyUser = function (name, password) {
  return new Promise(function (fulfill, reject) {
    UsersAdapter.findByName(name)
    .then(function (user) {
      if (user) {
        if (password && user.password == sha256(password)) {
          fulfill(user);
        } else {
          reject('Invalid password');
        }
      } else {
        reject('Unknown user name');
      }
    });
  });
};

//
// Retrieve user profile for its GET route
module.exports.retrieveUserProfile = function (req, res) {
  return new Promise(function (fulfill, reject) {
    UsersAdapter.findById(req.user.id).then(function (user) {
      const errors = req.session.errors;

      req.session.errors = null;
      req.session.save(function () {
        fulfill({ user: user, errors: errors });
      });
    });
  });
};

//
// Redirect the browser from an ajax request
function ajaxRedirect(res, url) {
  const data = JSON.stringify(url);

  res.contentType('application/json');
  res.header('Content-Length', data.length);
  res.end(data);
}

//
// Save user session data (like errors) then redirect
function saveSessionAndRedirect(req, res, redirect) {
  req.session.save(function () {
    ajaxRedirect(res, redirect);
  });
}

function pushErrorInUserSession(req, request, reason) {
  req.session.errors = (req.session.errors ? req.session.errors : []);
  req.session.errors.push({ request: request, reason: reason });
}

// Check new user name, set model field to update, or reject with error
function prepareUserNameUpdate(userModel, userUpdateRequest, fieldsToUpdate, reject) {
  var error = null;

  if (userUpdateRequest.name) {
    if (!(error = checkNewUserName(userUpdateRequest.name))) {
      userModel.name = userUpdateRequest.name;
      fieldsToUpdate.push('name');
    } else {
      reject(error + 'for user id ' + userUpdateRequest.id);
    }
  }
}

// Check new user email, set model field to update, or reject with error
function prepareUserEmailUpdate(userModel, userUpdateRequest, fieldsToUpdate, reject) {
  var error = null;

  if (userUpdateRequest.email) {
    if (!(error = checkNewUserEmail(userUpdateRequest.email))) {
      userModel.email = userUpdateRequest.email;
      fieldsToUpdate.push('email');
    } else {
      reject(error + 'for user id ' + userUpdateRequest.id);
    }
  }
}

// Check new user password, set model field to update, or reject with error
function prepareUserPasswordUpdate(userModel, userUpdateRequest, fieldsToUpdate, reject) {
  var error = null;

  if (userUpdateRequest.password) {
    if (!(error = checkNewUserPassword(userUpdateRequest.password, userUpdateRequest.confirmation))) {
      userModel.password = sha256(userUpdateRequest.password);
      fieldsToUpdate.push('password');
    } else {
      reject(error + 'for user id ' + userUpdateRequest.id);
    }
  }
}

// Update user profile, if possible, or reject with error
function updateUserProfile(userModel, userUpdateRequest) {
  return new Promise(function (fulfill, reject) {
    const fieldsToUpdate = [];

    prepareUserNameUpdate(userModel, userUpdateRequest, fieldsToUpdate, reject);
    prepareUserEmailUpdate(userModel, userUpdateRequest, fieldsToUpdate, reject);
    prepareUserPasswordUpdate(userModel, userUpdateRequest, fieldsToUpdate, reject);

    if (!fieldsToUpdate.length) {
      reject('No update needed for user id ' + userUpdateRequest.id);
    }

    fulfill(userModel.save({ fields: fieldsToUpdate }));
  });
}

//
// Update user profile entry point from its POST route
module.exports.updateUserProfile = function (params) {
  return function (req, res) {
    const userUpdate = {};

    userUpdate.name = req.body.username ? req.body.username : null;
    userUpdate.email = req.body.email ? req.body.email : null;
    userUpdate.password = req.body.password ? req.body.password : null;
    userUpdate.confirmation = req.body.confirmation ? req.body.confirmation : null;
    updateUserProfile(req.user, userUpdate)
    .then(function (user) {
      res.redirect(params.successRedirect);
    })
    .catch(function (error) {
      pushErrorInUserSession(req, userUpdate, error);
      res.redirect(params.failureRedirect);
    });
  };
};
