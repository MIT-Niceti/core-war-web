const compilerAddon = require('../cpp/build/Release/compiler.node');

module.exports.compile = function (inputFile, outputFile) {
  return new Promise(function (fulfill, reject) {
    var compilationStatus = null;

    try {
      compilationStatus = compilerAddon.compile(inputFile, outputFile);
    } catch (e) {
      reject('Compiler crash: ' + e.message);
    }

    try {
      fulfill(JSON.parse(compilationStatus));
    } catch (e) {
      reject('Json parsing error: ' + e.message);
    }
  });
};
