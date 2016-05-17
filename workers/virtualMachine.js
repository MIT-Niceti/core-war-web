const virtualMachineAddon = require('../cpp/build/Release/virtualMachine.node');

module.exports.launch = function () {
  return new Promise(function (fulfill, reject) {
    const coreDump = virtualMachineAddon.setVirtualMachine('lol', 'prout');
    console.log('done game');
    fulfill(coreDump);
  });
};
