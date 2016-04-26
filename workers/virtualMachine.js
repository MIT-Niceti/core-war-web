const virtualMachineAddon = require('../cpp/build/Release/virtualMachine.node');

modules.export.launch = function () {
  return new Promise(function (fulfill, reject) {
    const coreDump = virtualMachineAddon.setVirtualMachine('lol', 'prout');

    fulfill(coreDump);
  });
};
