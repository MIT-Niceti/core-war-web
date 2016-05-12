const virtualMachineAddon = require('../cpp/build/Release/virtualMachine.node');

module.exports.launch = function () {
  return new Promise(function (fulfill, reject) {
    const coreDump = virtualMachineAddon.setVirtualMachine('lol', 'prout');

    console.log('ok');
    console.log('yeah');
    fulfill(coreDump);
  });
};
