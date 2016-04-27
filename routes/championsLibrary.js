const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

module.exports = function initChampionsLibraryRoutes(app, conf) {
  //
  //// GET requests

  app.get('/champions_library.html',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      res.render('champions_library', { user: req.user });
    }
  );
};
