const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const arenaController = require('../adapters/virtualMachine');
const lobbiesManager = require('../managers/lobbies');


module.exports = function initArenaRoutes(app, conf, libs) {
  //
  //// GET requests
  var io = libs.io;

  app.get('/arena.html/:lobby',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      var champions = [];
      lobbiesManager.getUsersChampion(req.params.lobby).then(function (retArray)
      {
        arenaController.launchVirtualMachine(retArray.championArray).then(function (data) {
          try {
            console.log('Rendering');
            var lobby = io.of('/' + req.params.lobby).on('connection', function (socket) {
              lobby.emit(req.params.lobby, { coreDump: data });
              socket.emit(req.params.lobby, { coreDump: data });
            });

            res.redirect('/lobbies.html/' + req.params.lobby + '/result');
          }
          catch (e) {
            console.log('Error: ' + e);
            res.redirect('/lobbies.html/');
          }
        });
      });
    }
  );
};
