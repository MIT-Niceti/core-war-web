const virtualMachineWorker = require('../workers/virtualMachine');

module.exports.launchVirtualMachine = function (championArray) {
  return virtualMachineWorker.launch(championArray);
};
