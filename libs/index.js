module.exports = function initNodeLibraries(conf) {
  const libs = {};

  require('./express')(libs);
  require('./socket.io')(libs);
  require('./passport')(libs);
  require('./passport.socket.io')(libs);
  require('./sequelize')(libs, conf);
  require('./sequelize.session')(libs, conf);
  require('./ejs')(libs, conf);
  return libs;
};
