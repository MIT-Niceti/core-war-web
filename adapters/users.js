const UsersModel = require('../models/Users');
const championsAdapter = require('./champions');

module.exports.findById = function (id) {
  return UsersModel.findOne({ _id: id }).populate('champions');
};

module.exports.findByName = function (name) {
  return UsersModel.findOne({ name: name }).populate('champions');
};

module.exports.findByEmail = function (email) {
  return UsersModel.findOne({ email: email }).populate('champions');
};

module.exports.addChampion = function (user, champion) {
  return new Promise(function (fulfill, reject) {
    user.champions.push(champion._id);
    user.save(function (error) {
      if (error) {
        reject(error);
      } else {
        fulfill(user);
      }
    });
  });
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
