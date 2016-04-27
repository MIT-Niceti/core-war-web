const virtualMachineWorker = require('../workers/virtualMachine');

module.exports.launchVirtualMachine = function () {
  return virtualMachineWorker.launch();
};
