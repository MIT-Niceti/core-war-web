module.exports = function initExpress(conf) {
  // include libraries
  const express = require('express');
  const cookieParser = require('cookie-parser');
  const bodyParser = require('body-parser');
  const morgan = require('morgan');

  // init express
  const app = express();

  // init global middleware
  app.use(cookieParser(conf.secret));
  app.use(bodyParser.urlencoded({ extended: true }));
  app.use(morgan('combined'));

  require('./ejs')(app, conf);
  require('./mongoose.session')(app, conf);

  return app;
};
