const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const arenaController = require('../adapters/virtualMachine');

module.exports = function initArenaRoutes(app, conf) {
  //
  //// GET requests

  app.get('/arena.html',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      arenaController.launchVirtualMachine().then(function (data) {
        try {
          res.render('arena', { user: req.user, arena: data });
        }
        catch (e) {
          console.log('Error: ' + e);
          res.redirect('/lobbies.html/');
        }
      });
    }
  );
};
