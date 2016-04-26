const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

module.exports = function initLobbiesRoutes(app, conf) {
  //
  //// GET requests

  app.get('/lobbies.html',
    function (req, res) {
      res.render('lobbies', { user: req.user });
    }
  );
};
