//
// Lobbies controller interface

const lobbiesManager = require('../managers/lobbies');

module.exports.addLobby = function (params) {
  return lobbiesManager.createLobby(params);
};

module.exports.getLobbies = function (req, res) {
  return lobbiesManager.getLobbies(req, res);
};

module.exports.getLobby = function (lobby) {
  return lobbiesManager.getLobby(lobby);
};

module.exports.removeLobby = function (lobby) {
  return lobbiesManager.removeLobby(lobby);
};

module.exports.removeUser = function (lobby, userId) {
  return lobbiesManager.removeUser(lobby, userId);
};

module.exports.getUserStatus = function (lobby, userId) {
  return lobbiesManager.getUserStatus(lobby, userId);
};

module.exports.joinLobby = function (lobby, userId) {
  return lobbiesManager.joinLobby(lobby, userId);
};
