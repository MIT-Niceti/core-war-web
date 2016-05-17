const LobbiesAdapter = require('../adapters/lobbies');
const UsersAdapter = require('../adapters/users');

function checkAndCreateLobby(name, creator, maxPlayers)
{
  return new Promise(function (fulfill, reject) {
    if (!name.length || maxPlayers == 0) {
      reject('Error. Missing lobby name/max players');
    }

    LobbiesAdapter.findByName(name)
    .then(function (lobby) {
        if (!lobby) {
          LobbiesAdapter.createLobby(name, creator, maxPlayers)
            .then(function (lobby) {
              fulfill(lobby);
            }).catch(function (error) {
              reject(error);
            });
        } else {
          reject('A lobby already exists with this name ' + name);
        }
      });
  });
}

module.exports.removeUser = function (id, userId)
{
  return new Promise(function (fullfill, reject) {
    console.log('Step 3 ' + id + ' user ' + userId);
    LobbiesAdapter.findById(id).then(function (lobby) {
      console.log('Lobby is : ' + lobby);
      var index = lobby.members.indexOf(userId);
      lobby.members.forEach(function (member) {
          if (member == userId && member != lobby.creator)
          {
            lobby.members.splice(index, 1);
            lobby.save();
            getUsersNames(lobby);
            console.log('Lobby: ' + lobby);
            fullfill({ lobby: lobby });
          }
        });

      fullfill({ lobby: lobby });
    });
  });
};

module.exports.getUserStatus = function (id, userId)
{
  return new Promise(function (fullfill, reject) {
    status = -1;
    LobbiesAdapter.findById(id).then(function (lobby) {
      if (lobby.creator == userId)
        fullfill({ status: 'creator' });
      else
      {
        lobby.members.forEach(function (member) {
          if (member == userId)
            fullfill({ status: 'member' });
        });
      }

      fullfill({ status: 'nothing' });
    });
  });
};

module.exports.joinLobby = function (id, userId) {
  return new Promise(function (fullfill, reject) {
    flag = 0;
    LobbiesAdapter.findById(id).then(function (lobby) {
      if (lobby.maxPlayers == lobby.members.length) {
        flag = 1;
        reject('Lobby is full');
      }

      lobby.members.forEach(function (member) {
        if (member == userId) {
          flag = 1;
          reject('You are already member of this lobby.');
        }
      });

      if (!flag) {
        lobby.members.push(userId);
        lobby.save();
        fullfill({ id: id });
      }
    });
  });
};

function getUsersNames(lobby)
{
  var flag = 0;
  lobby.members.forEach(function (userId) {
    var data = [];
    counter = 0;
    UsersAdapter.findById(userId).then(function (user) {
      data.push(user);
      if (++counter == lobby.members.length)
      {
        flag = 1;
        lobby.users = data;
      }
    });
  });

  if (flag == 1)
    return;
}

module.exports.getLobby = function (id) {
  return new Promise(function (fullfill, reject) {
    var data = [];
    counter = 0;
    LobbiesAdapter.findById(id).then(function (lobby) {
      lobby.users = [];
      lobby.members.forEach(function (userId) {
        UsersAdapter.findById(userId).then(function (user) {
          //console.log('found: ' + user);
          data.push(user);
          if (++counter == lobby.members.length)
          {
            lobby.users = data;
            fullfill({ lobby: lobby });
          }
        });
      });
    });
  });
};

module.exports.getLobbies = function (req, res)
{
  return new Promise(function (fulfill, reject) {
    LobbiesAdapter.getLobbies().then(function (lobbies) {
      const errors = req.session.errors;
      req.session.errors = null;
      req.session.save(function () {
        fulfill({ lobbies: lobbies, errors: errors, user: req.user });
      });
    });
  });
};

module.exports.removeLobby = function (id) {
  return new Promise(function (fullfill, reject) {
    var data = [];
    counter = 0;
    LobbiesAdapter.findById(id).then(function (lobby) {
      lobby.remove(function () {
        fullfill();
      });
    });
  });
};

//
// Create lobby entry point from its POST route
module.exports.createLobby = function (params) {
  return function (req, res) {
    checkAndCreateLobby(req.body.name, req.user.id, req.body.maxPlayers)
      .then(function (lobby) {
        req.session.save(function () {
          console.log('connected ' + lobby._id);
          params.io.of('/' + lobby._id).on('disconnect', function (socket)
                {
                  console.log('proutiprouta');
                }
              );
          /*params.io.of('/' + lobby._id).on('disconnect', function (socket)
              {
                  console.log('prout PROUT PROUT PROUT');
              }
            );*/

        });
        console.log('created socket');
        res.redirect(params.successRedirect);
      }).catch(function (error) {
        res.redirect(params.failureRedirect);
      }
    );
  };
};
