const compilerWorker = require('../workers/compiler');

module.exports.compile = function (inputFile, outputFile) {
  return new Promise(function (fulfill, reject) {

    compilerWorker.compile(inputFile, outputFile)
    .then(function (output) {
      const fullOutput = output;

      fullOutput.inputFileName = inputFile;
      fullOutput.outputFile = outputFile;
      fulfill(fullOutput);
    }).catch(function (error) {
      reject(error);
    });

  });
};
