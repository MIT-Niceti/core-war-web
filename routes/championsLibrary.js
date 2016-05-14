const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const championsLibraryController = require('../controllers/championsLibrary');

module.exports = function initChampionsLibraryRoutes(app, conf) {
  //
  //// GET requests

  app.get('/champions_library.html',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      championsLibraryController.compile().then(function (result) {
        console.log('Again: ' + result);
        res.render('champions_library', { user: req.user, compilerResult: result });
      });
    }
  );
};
