module.exports = function initSequelizeSession(libs, conf) {
  const sessionConf = conf.http.session;

  libs.session = require('express-session');
  libs.Store = require('connect-session-sequelize')(libs.session.Store);
  libs.store = new libs.Store({ db: libs.sequelize });

  libs.app.use(libs.session({
    name: sessionConf.name,
    secret: sessionConf.secret,
    store: libs.store,
    resave: false,
    saveUninitialized: true,
  }));

  libs.app.use(libs.passport.session());

  libs.sequelize.sync({ force: true });
};
