module.exports = function initRoutes(app, conf) {
  require('./default')(app, conf);
  require('./users')(app, conf);
};
