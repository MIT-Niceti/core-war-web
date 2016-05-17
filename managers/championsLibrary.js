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

function downloadAssemblyFile(req, res)
{
  return new Promise(function (fulfill, reject) {
    if (req.files && req.files.assemblyFile) {
      const assemblyFile = req.files.assemblyFile;
      const inputDirectoryPath = path.join(compilerConfig.upload, req.user._id.toString());
      const inputFilePath = path.join(inputDirectoryPath, assemblyFile.name);

      // console.log(inputDirectoryPath);
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
          console.log('compiled champion path ' + champion.path);
          compilerAdapter.compile(localFilePath, champion.path)
          .then(function (compilationOutput) {
            req.session.compilationOutput = compilationOutput;
            usersAdapter.addChampion(req.user, champion)
            .then(function (user) {
              saveSessionAndRedirect(req, res, params.successRedirect);
            }).catch(function (error) {
              champion.remove();
              pushErrorInUserSession(req, 'add new champion error', error);
              saveSessionAndRedirect(req, res, params.failureRedirect);
            });
          }).catch(function (error) {
            champion.remove();
            pushErrorInUserSession(req, 'compilation error', error);
            saveSessionAndRedirect(req, res, params.failureRedirect);
          });
        }).catch(function (error) {
          champion.remove();
          pushErrorInUserSession(req, 'cannot create output directory', error);
          saveSessionAndRedirect(req, res, params.failureRedirect);
        });
      }).catch(function (error) {
        pushErrorInUserSession(req, 'cannot create champion', error);
        saveSessionAndRedirect(req, res, params.failureRedirect);
      });
    }).catch(function (error) {
      pushErrorInUserSession(error);
      res.status(500).send(error);
    });
  };
};

module.exports.deleteChampion = function (params) {
  return function (req, res) {
    console.log('user want to delete his champion with id ' + req.params.championId);
    req.session.deletedChampion = { _id: req.params.championId };

    req.session.save(function () {
      res.redirect(params.successRedirect);
    });
  };
};
