module.exports = function initPassport(libs) {
  libs.passport = require('passport');
  libs.LocalStrategy = require('passport-local');

  libs.app.use(libs.passport.initialize());
};
