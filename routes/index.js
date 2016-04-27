module.exports = function initRoutes(app, conf) {
  require('./main')(app, conf);
  require('./users')(app, conf);
  require('./champions_library')(app, conf);
  require('./lobbies')(app, conf);
  require('./arena')(app, conf);
};
