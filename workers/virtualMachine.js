const virtualMachineAddon = require('../cpp/build/Release/virtualMachine.node');

module.exports.launch = function (championArray) {
  return new Promise(function (fulfill, reject) {
    const coreDump = virtualMachineAddon.setVirtualMachine.apply(null, championArray);
    console.log('done game');
    fulfill(coreDump);
  });
};
