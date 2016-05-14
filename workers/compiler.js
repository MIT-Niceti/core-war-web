const compilerAddon = require('../cpp/build/Release/compiler.node');

module.exports.compile = function (inputFile, outputFile) {
  return new Promise(function (fulfill, reject) {
    const compilationStatus = compilerAddon.compile(inputFile, outputFile);

    try {
      fulfill(JSON.parse(compilationStatus));
    } catch (e) {
      reject('Error: ' + e.message);
    }
  });
};
