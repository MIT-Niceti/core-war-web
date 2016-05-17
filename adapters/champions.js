const ChampionsModel = require('../models/Champions');
const path = require('path');

module.exports.findById = function (id) {
  return ChampionsModel.findOne({ _id: id });
};

module.exports.findByName = function (name) {
  return ChampionsModel.findOne({ name: name });
};

module.exports.createChampion = function (name, rootPath) {
  return new Promise(function (fulfill, reject) {
    if (name && name.length && rootPath && rootPath.length) {
      ChampionsModel.create({ name: name, path: rootPath }, function (err, champion) {
        if (err) {
          reject(err);
        } else {
          champion.path = path.join(rootPath, champion._id.toString());
          champion.save(function (error) {
            if (err) {
              reject(err);
            } else {
              fulfill(champion);
            }
          });
        }
      });
    } else {
      reject('Found empty field while creating champion');
    }
  });
};
