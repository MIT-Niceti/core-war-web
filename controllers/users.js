//
// Users controller interface

const usersManager = require('../managers/users');

module.exports.createUser = function (params) {
  return usersManager.createUser(params);
};

module.exports.retrieveUserProfile = function (req, res) {
  return usersManager.retrieveUserProfile(req, res);
};

module.exports.updateUserProfile = function (params) {
  return usersManager.updateUserProfile(params);
};

module.exports.identifyUser = function (name, password) {
  return usersManager.identifyUser(name, password);
};
