const virtualMachineWorker = require('../workers/virtualMachine');

modules.export.launchVirtualMachine = function () {
  return virtualMachineWorker.launchVirtualMachine();
};
