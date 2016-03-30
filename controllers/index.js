module.exports = function runMainController(conf, libs) {
  const managers = require(conf.rootFolder + '/managers')(conf, libs);
  const controllers = {};

  require('./users')(conf, libs, managers);
  require('./champions')(conf, libs, managers);
  require('./arenas')(conf, libs, managers);
  require('./matchmaking')(conf, libs, managers);
  require('./routes')(conf, libs, managers);
  const addon = require('../build/Release/virtualMachine.node');

  console.log(addon.setVirtualMachine("lol", "prout")); // 'world'
};
