const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const lobbyController = require('../controllers/lobbies');

module.exports = function initLobbiesRoutes(app, conf) {
  //
  //// GET requests

  app.get('/lobbies.html',
  ensureLoggedIn('/index.html'),
  function (req, res) {
    if (!req.query.lobby)
    {
      lobbyController.getLobbies(req, res)
      .then(function (data) {
        console.log('Data to lobbies: ' + data);
        res.render('lobbies', data);
      });
    }
  }
  );

  app.get('/lobbies.html/:lobby/view',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      lobbyController.getLobby(req.params.lobby)
      .then(function (data) {
        if (data)
        {
          flag = 0;
          lobbyController.getUserStatus(req.params.lobby, req.user.id).then(function (status)
          {
            data.user = req.user;
            if (status)
              data.status = status.status;
            else
              data.status = 'nothing';
            console.log('Lobby: ' + data.lobby);
            res.render('profileLobby', data);
          });
        }
      });
    }
  );

  app.get('/lobbies.html/:lobby/kick/:userId',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      lobbyController.getLobby(req.params.lobby)
      .then(function (data) {
        if (data)
        {
          flag = 0;
          lobbyController.getUserStatus(req.params.lobby, req.user.id).then(function (status)
          {
            console.log('Step 1 status ' + status.status);
            data.user = req.user;
            if (status)
            {
              if (status.status == 'creator')
              {
                console.log('ok');
                lobbyController.removeUser(req.params.lobby, req.params.userId).then(function (lobby)
                {
                  console.log('yes');
                  res.redirect('/lobbies.html/' + req.params.lobby + '/view');
                });
              } else {
                res.redirect('/lobbies.html/' + req.params.lobby + '/view');
              }
            }
          });
        }
      });
    }
  );

  app.get('/lobbies.html/:lobby/leave',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      lobbyController.getLobby(req.params.lobby)
      .then(function (data) {
        if (data)
        {
          flag = 0;
          lobbyController.getUserStatus(req.params.lobby, req.user.id).then(function (status)
          {
            data.user = req.user;
            if (status)
            {
              if (status.status == 'member')
              {
                lobbyController.removeUser(req.params.lobby, req.user.id).then(function (lobby)
                {
                  res.redirect('/lobbies.html/' + req.params.lobby + '/view');
                });
              }
            }
          });
        }
      });
    }
  );

  app.get('/lobbies.html/:lobby/erase',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      lobbyController.getLobby(req.params.lobby)
      .then(function (data) {
        if (data)
        {
          flag = 0;
          lobbyController.getUserStatus(req.params.lobby, req.user.id).then(function (status)
          {
            data.user = req.user;
            if (status)
            {
              if (status.status == 'creator')
              {
                lobbyController.removeLobby(req.params.lobby).then(function ()
                {
                  res.redirect('/lobbies.html/');
                });
              } else {
                res.redirect('/lobbies.html/' + req.params.lobby + '/view');
              }
            }
          });
        }
      });
    }
  );

  app.get('/lobbies.html/:lobby/join',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      lobbyController.joinLobby(req.params.lobby, req.user.id)
      .then(function (data) {
        if (data)
        {
          lobbyController.getLobby(data.id)
          .then(function (data) {
            if (data)
            {
              data.user = req.user;
              res.redirect('/lobbies.html/' + req.params.lobby + '/view');
            }
          });
        }
      })
      .catch(function (error) {
        res.redirect('/lobbies.html/' + req.params.lobby + '/view');
      });
    }
  );

  app.get('/addLobby.html',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      res.render('addLobby', { user: req.user });
    }
  );

  //
  //// POST requests

  app.post('/addLobby',
  ensureLoggedIn('/index.html'),
     lobbyController.addLobby({
       successRedirect: '/lobbies.html',
       failureRedirect: '/index.html',
     })
  );
};
