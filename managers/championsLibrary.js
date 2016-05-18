const mkdir = require('mkdirp');
const path = require('path');
const compilerAdapter = require('../adapters/compiler');
const usersAdapter = require('../adapters/users');
const championsAdapter = require('../adapters/champions');
const compilerConfig = require('../config/app.config.json').compilerLibrary;

//
// Save user session data (like errors) then redirect
function saveSessionAndRedirect(req, res, redirect) {
  req.session.save(function () {
    res.redirect(redirect);
  });
}

function pushErrorInUserSession(req, request, reason) {
  req.session.errors = (req.session.errors ? req.session.errors : []);
  req.session.errors.push({ request: request, reason: reason });
}

module.exports.retrieveUserChampionsLibrary = function (req, res) {
  return new Promise(function (fulfill, reject) {
    const data = {
      user: req.user,
      champions: req.user.champions,
      compilationOutput: req.session.compilationOutput,
      deletedChampion: req.session.deletedChampion,
      errors: req.session.errors,
    };

    req.session.errors = null;
    req.session.compilationOutput = null;
    req.session.deletedChampion = null;
    req.session.save(function () {
      fulfill(data);
    });
  });
};

function downloadAssemblyFile(req, res) {
  return new Promise(function (fulfill, reject) {
    if (req.files && req.files.assemblyFile && req.files.assemblyFile.data[0] !== undefined) {
      const assemblyFile = req.files.assemblyFile;
      const inputDirectoryPath = path.join(compilerConfig.upload, req.user._id.toString());
      const inputFilePath = path.join(inputDirectoryPath, assemblyFile.name);

      mkdir(inputDirectoryPath, function (error) {
        if (error) {
          reject('Cannot create champion input directory');
        } else {
          assemblyFile.mv(inputFilePath, function (error) {
            if (error) {
              reject(error);
            } else {
              fulfill(inputFilePath);
            }
          });
        }
      });
    } else {
      reject('No file has been uploaded');
    }
  });
}

function createOutputDirectoryForUser(user) {
  return new Promise(function (fulfill, reject) {
    const outputDirectoryPath = path.join(compilerConfig.compiled, user._id.toString());

    mkdir(outputDirectoryPath, function (error) {
      if (error) {
        reject(error);
      } else {
        fulfill(outputDirectoryPath);
      }
    });
  });
}

module.exports.compileChampion = function (params) {
  return function (req, res) {

    downloadAssemblyFile(req, res)
    .then(function (localFilePath) {
      championsAdapter.createChampion(req.body.championName, path.join(compilerConfig.compiled, req.user._id.toString()))
      .then(function (champion) {
        createOutputDirectoryForUser(req.user)
        .then(function (outputDirectory) {
          compilerAdapter.compile(localFilePath, champion.path)
          .then(function (compilationOutput) {
            req.session.compilationOutput = compilationOutput;

            if (compilationOutput.status) {
              usersAdapter.addChampion(req.user, champion)
              .then(function (user) {
                saveSessionAndRedirect(req, res, params.successRedirect);
              }).catch(function (error) {
                champion.remove();
                pushErrorInUserSession(req, 'Champion creation', error);
                saveSessionAndRedirect(req, res, params.failureRedirect);
              });
            } else {
              pushErrorInUserSession(req, 'Invalid champion', 'compilation failure');
              saveSessionAndRedirect(req, res, params.failureRedirect);
            }

          }).catch(function (error) {
            champion.remove();
            pushErrorInUserSession(req, 'Compilation error', error);
            saveSessionAndRedirect(req, res, params.failureRedirect);
          });
        }).catch(function (error) {
          champion.remove();
          pushErrorInUserSession(req, 'Output directory', error);
          saveSessionAndRedirect(req, res, params.failureRedirect);
        });
      }).catch(function (error) {
        pushErrorInUserSession(req, 'Champion creation', error);
        saveSessionAndRedirect(req, res, params.failureRedirect);
      });
    }).catch(function (error) {
      pushErrorInUserSession(req, 'File downloader', error);
      saveSessionAndRedirect(req, res, params.failureRedirect);
    });
  };
};

function deleteChampion(championId, user) {
  return new Promise(function (fulfill, reject) {
    var championToDelete = null;

    for (var i = 0; !championToDelete && i != user.champions.length; ++i) {
      const champion = user.champions[i];

      if (champion._id.toString() == championId) {
        user.champions.splice(i, i);
        championToDelete = champion;
      }
    }

    if (championToDelete) {
      championToDelete.remove(function () {
        user.save(function (error) {
          if (error) {
            reject(error);
          } else {
            fulfill(championToDelete);
          }
        });
      });
    } else {
      reject('champion not found');
    }
  });
}

module.exports.deleteChampion = function (params) {
  return function (req, res) {
    if (!req.params || !req.params.championId) {
      pushErrorInUserSession(req, 'invalid parameter', 'champion id');
      saveSessionAndRedirect(req, res, params.failureRedirect);
    } else {
      deleteChampion(req.params.championId, req.user)
      .then(function (deletedChampion) {
        req.session.deletedChampion = deletedChampion;
        checkAndRemoveSelectedChampion(deletedChampion, req.user)
        .then(function (user) {
          req.user = user;
          saveSessionAndRedirect(req, res, params.successRedirect);
        }).catch(function (error) {
          pushErrorInUserSession(req, 'Champion unselection', error);
          saveSessionAndRedirect(req, res, params.failureRedirect);
        });
      })
      .catch(function (error) {
        pushErrorInUserSession(req, 'Cannot delete champion', error);
        saveSessionAndRedirect(req, res, params.failureRedirect);
      });
    }
  };
};

function checkAndRemoveSelectedChampion(champion, user) {
  return new Promise(function (fulfill, reject) {
    if (user.selectedChampion && user.selectedChampion._id.equals(champion._id)) {
      user.selectedChampion = null;
      user.save(function (error) {
        if (error) {
          reject(error);
        } else {
          fulfill(user);
        }
      });
    } else {
      fulfill(user);
    }
  });
}

module.exports.selectChampion = function (params) {
  return function (req, res) {
    if (!req.params || !req.params.championId) {
      pushErrorInUserSession(req, 'Invalid parameter', 'champion id');
      saveSessionAndRedirect(req, res, params.failureRedirect);

    } else {
      usersAdapter.selectChampion(req.user, req.params.championId)
      .then(function (user) {
        req.user = user;
        saveSessionAndRedirect(req, res, params.successRedirect);
      })
      .catch(function (error) {
        pushErrorInUserSession(req, 'Champion selection', error);
        saveSessionAndRedirect(req, res, params.failureRedirect);
      });

    }
  };
};
