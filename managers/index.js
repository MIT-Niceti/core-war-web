module.exports = function initManagers(conf, libs) {
  const managers = {};

  managers.users = require('./users');
  return managers;
};
