const mongoose = require('./mongoose');

module.exports = function initMongooseSession(app, conf) {
  const Store = require('express-session').Store;
  const MongooseStore = require('mongoose-express-session')(Store);

  app.use(require('express-session')({
    secret: conf.http.session.secret,
    resave: false,
    rolling: false,
    saveUninitialized: true,
    store: new MongooseStore({ connection: mongoose }),
  }));
};
