const UsersModel = require('../models/Users');

module.exports.findById = function (id) {
  return UsersModel.findOne({ _id: id });
};

module.exports.findByName = function (name) {
  return UsersModel.findOne({ name: name });
};

module.exports.findByEmail = function (email) {
  return UsersModel.findOne({ email: email });
};

module.exports.createUser = function (name, email, password) {
  return new Promise(function (fulfill, reject) {
    UsersModel.create({ name: name, email: email, password: password }, function (err, user) {
      if (err) {
        reject(err);
      } else {
        fulfill(user);
      }
    });
  });
};
