const express = require('express');

const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const lobbyController = require('../controllers/lobbies');



module.exports = function initLobbiesRoutes(app, conf, libs) {
  //
  //// GET requests
  var io = libs.io;

  app.get('/lobbies.html',
  ensureLoggedIn('/index.html'),
  function (req, res) {
    if (!req.query.lobby)
    {
      lobbyController.getLobbies(req, res)
      .then(function (data) {
        res.render('lobbies', data);
      });
    }
  }
  );

  app.get('/lobbies.html/:lobby/result',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      console.log('Result');
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
            console.log('End result');
            res.render('resultLobby', data);
          });
        }
      });
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
              res.redirect('/lobbies.html/' + req.params.lobby + '/view');
            res.render('profileLobby', data);
          });
        }
        else {
          res.redirect('lobbies.html/');
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
                  res.redirect('/lobbies.html/');
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
                  var room = io.of('/' + req.params.lobby).emit('cancel', { cancel : 'canceled' });
                  if (io.sockets.adapter.rooms[req.params.lobby] >= 1) {
                    io.sockets.clients(req.params.lobby).forEach(function (s) {
                      if (s)
                        s.leave(req.params.lobby);
                    });
                  }
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
              res.redirect('/lobbies.html/' + req.params.lobby + '/result');
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
       io: libs.io,
       successRedirect: '/lobbies.html',
       failureRedirect: '/index.html',
     })
  );
};
