const UserModel = require('../models/User');

module.exports.findAll = function () {
  return UserModel.findAll({
    attributes: ['id', 'name', 'email'],
  });
};

module.exports.findById = function (id) {
  return UserModel.findOne({ id: id });
};

module.exports.findByName = function (name) {
  return UserModel.findOne({ name: name });
};

module.exports.findByEmail = function (email) {
  return UserModel.findOne({ email: email });
};

module.exports.createUser = function (name, email, password) {
  return new Promise(function (fulfill, reject) {
    UserModel.create({ name: name, email: email, password: password }, function (err, user) {
      if (err) {
        reject(err);
      } else {
        fulfill(user);
      }
    });
  });
};
