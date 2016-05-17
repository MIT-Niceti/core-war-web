const championsLibraryManager = require('../managers/championsLibrary');

module.exports.retrieveUserChampionsLibrary = function (res, req) {
  return championsLibraryManager.retrieveUserChampionsLibrary(res, req);
};

module.exports.compileChampion = function (params) {
  return championsLibraryManager.compileChampion(params);
};

module.exports.deleteChampion = function (params) {
  return championsLibraryManager.deleteChampion(params);
};
