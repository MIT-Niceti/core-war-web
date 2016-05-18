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
      championsLibraryController.retrieveUserChampionsLibrary(req, res)
      .then(function (data) {
        res.render('champions_library', data);
      });
    }
  );

  //
  //// POST requests

  app.post('/compile_champion',
    ensureLoggedIn('/index.html'),
    championsLibraryController.compileChampion({
      successRedirect: '/champions_library.html',
      failureRedirect: '/champions_library.html',
    })
  );

  app.post('/delete_champion/:championId',
    ensureLoggedIn('/index.html'),
    championsLibraryController.deleteChampion({
      successRedirect: '/champions_library.html',
      failureRedirect: '/champions_library.html',
    })
  );

  app.post('/select_champion/:championId',
    ensureLoggedIn('/index.html'),
    championsLibraryController.selectChampion({
      successRedirect: '/champions_library.html',
      failureRedirect: '/champions_library.html',
    })
  );
};
