const compilerAdapter = require('../adapters/compiler');

module.exports.retrieveUserChampionsLibrary = function (req, res) {
  return new Promise(function (fulfill, reject) {
    const rawValue = [
      { _id: '3516516', name: 'hellboy', inputFileName: 'hellboy42.s', creationDate: '10/10/10 23h42' },
      { _id: '4242', name: 'wolverine', inputFileName: 'wolverine.s', creationDate: '21/21/00 23h42' },
    ];
    const data = { user: req.user, champions: rawValue, compilationOutput: req.session.compilationOutput, deletedChampion: req.session.deletedChampion };

    if (req.session.compilationOutput) {
      req.session.compilationOutput = null;
    }

    if (req.session.deletedChampion) {
      req.session.deletedChampion = null;
    }

    req.session.save(function () {
      fulfill(data);
    });
  });
};

module.exports.compileChampion = function (params) {
  return function (req, res) {
    console.log('compile champion');

    compilerAdapter.compile('./cpp/compiler/champion.s', './my_champion.out')
    .then(function (compilationOutput) {
      req.session.compilationOutput = compilationOutput;

      req.session.save(function () {
        res.redirect(params.successRedirect);
      });
    }).catch(function (error) {
      res.redirect(params.failureRedirect);
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
