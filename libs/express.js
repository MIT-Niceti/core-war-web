module.exports = function initExpress(libs) {
  libs.express = require('express');
  libs.app = libs.express();

  // Init global middleware
  libs.cookieParser = require('cookie-parser');
  libs.bodyParser = require('body-parser');
  libs.morgan = require('morgan');

  libs.app.use(libs.morgan('combined'));
  libs.app.use(libs.cookieParser());
  libs.app.use(libs.bodyParser.urlencoded({ extended: true }));
};
