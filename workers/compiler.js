const compilerAddon = require('../cpp/build/Release/compiler.node');

module.exports.compile = function (inputFile, outputFile) {
  return new Promise(function (fulfill, reject) {
    const compilationStatus = compilerAddon.compile(inputFile, outputFile);

    console.log(compilationStatus);
    try {
      const output = JSON.parse(compilationStatus);

      fulfill(output);
    } catch (e) {
      reject('Error: ' + e.message);
    }
  });
};
