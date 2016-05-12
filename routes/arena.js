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
      arenaController.launchVirtualMachine().then(function (data) {
        try {
          console.log('Rendering');
          var lobby = io.of('/' + req.params.lobby).on('connection', function (socket) {
              console.log('lolol');
              socket.emit(req.params.lobby, { coreDump : data });
            });
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
