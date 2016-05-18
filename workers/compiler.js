const compilerAddon = require('../cpp/build/Release/compiler.node');

module.exports.compile = function (inputFile, outputFile) {
  return new Promise(function (fulfill, reject) {
    var compilationStatus = null;

    try {
      compilationStatus = compilerAddon.compile(inputFile, outputFile);
    } catch (e) {
      reject('Compiler crash: ' + e.message);
    }

    console.log(compilationStatus);
    try {
      const output = JSON.parse(compilationStatus);

      fulfill(output);
    } catch (e) {
      reject('Json parsing error: ' + e.message);
    }
  });
};
