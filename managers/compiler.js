const compilerWorker = require('../workers/compiler');

module.exports.compile = function () {
  return compilerWorker.compile('./cpp/compiler/champion.s', './my_champion.out');

  //   .then(function (result) {
  //     console.log('Compilation result: ' + result.status);
  //     console.log('Logs: ' + result.logs);
  //   }
  // );
};
