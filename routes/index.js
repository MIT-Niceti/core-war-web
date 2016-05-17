module.exports = function initRoutes(app, conf, libs) {
  require('./main')(app, conf);
  require('./users')(app, conf);
  require('./championsLibrary')(app, conf);
  require('./lobbies')(app, conf, libs);
  require('./arena')(app, conf, libs);
};
