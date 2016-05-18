const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const arenaController = require('../adapters/virtualMachine');

module.exports = function initArenaRoutes(app, conf, libs) {
  //
  //// GET requests
  var io = libs.io;

  app.get('/arena.html/:lobby',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      var champions = []
      champions.push('C:\\Users\\norman_e\\Pictures\\forker.out')
      champions.push('C:\\Users\\norman_e\\Pictures\\reference_champion.out')
      arenaController.launchVirtualMachine(champions).then(function (data) {
        try {
          console.log('Rendering');
          var lobby = io.of('/' + req.params.lobby).on('connection', function (socket) {
            lobby.emit(req.params.lobby, { coreDump : data });
            socket.emit(req.params.lobby, { coreDump : data });
          });
//          io.of('/' + req.params.lobby).emit(req.params.lobby, { coreDump : data });
        //  io.sockets.in(req.params.lobby).emit(req.params.lobby, { coreDump : data });
          res.redirect('/lobbies.html/' + req.params.lobby + '/result');
        }
        catch (e) {
          console.log('Error: ' + e);
          res.redirect('/lobbies.html/');
        }
      });
    }
  );
};
