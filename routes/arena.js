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
      console.log('Starting');
      lobbiesManager.getLobby(req.params.lobby).then(function (result)
      {
        var champions = [];
        if (result.lobby.creator != req.user.id || result.lobby.users.length < 2)
          res.redirect('/lobbies.html/');
        result.lobby.users.forEach(function (user) {
          if (user.selectedChampion)
            champions.push(user.selectedChampion.path);
        });
        arenaController.launchVirtualMachine(champions).then(function (data) {
          try {
            var lobby = io.of('/' + req.params.lobby).on('connection', function (socket) {
              lobby.emit(req.params.lobby, { coreDump: data });
              socket.emit(req.params.lobby, { coreDump: data });
            });
            lobbiesManager.removeLobby(req.params.lobby).then(function (){
              result.status = 'creator';
              result.user = req.user;
              res.render('resultLobby', result);
            });
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
