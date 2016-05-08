const LobbiesModel = require('../models/Lobbies');

module.exports.findById = function (id) {
  return LobbiesModel.findOne({ _id: id });
};

module.exports.findByName = function (name) {
  return LobbiesModel.findOne({ name: name });
};

module.exports.createLobby = function (name, creator, maxPlayers) {
  return new Promise(function (fulfill, reject) {
    LobbiesModel.create({ name: name, creator: creator, maxPlayers: maxPlayers, members: [creator] }, function (err, lobby) {
      if (err) {
        reject(err);
      } else {
        fulfill(lobby);
      }
    });
  });
};

module.exports.getLobbies = function () {
  return LobbiesModel.find();
};
