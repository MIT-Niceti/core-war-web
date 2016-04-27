const UsersManager = require('../managers/users');
const UsersAdapter = require('../adapters/users');

module.exports.localStrategy = function (username, password, done) {
  UsersManager.identifyUser(username, password)
  .then(function (user) {
    done(null, user);
  },

  function (error) {
    done(null, false, { message: error });
  });
};

module.exports.serializeUser = function (user, done) {
  if (user && user.id) {
    done(null, user.id);
  } else {
    done({ message: 'Passport serializer: Invalid user' }, null);
  }
};

module.exports.deserializeUser = function (id, done) {
  UsersAdapter.findById(id)
  .then(function (user) {
    if (user) {
      return done(null, user);
    } else {
      return done({ message: 'Passport deserializer: User not found' }, null);
    }
  });
};
