const virtualMachineAddon = require('../cpp/build/Release/virtualMachine.node');

module.exports.launch = function (championArray) {
  return new Promise(function (fulfill, reject) {
    console.log('Champions: ')
    console.log(championArray)
    const coreDump = virtualMachineAddon.setVirtualMachine.apply(virtualMachineAddon, championArray);
    console.log('done game');
    fulfill(coreDump);
  });
};
