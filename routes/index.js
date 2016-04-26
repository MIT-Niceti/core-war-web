module.exports = function initRoutes(app, conf) {
  require('./default')(app, conf);
  require('./users')(app, conf);
  require('./champions_library')(app, conf);
  require('./lobbies')(app, conf);
};
