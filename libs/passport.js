const passportManager = require('../managers/passport');

module.exports = function initPassport(app) {
  var passport = require('passport');
  var LocalStrategy = require('passport-local');

  app.use(passport.initialize());
  app.use(passport.session());

  passport.use(new LocalStrategy(passportManager.localStrategy));
  passport.serializeUser(passportManager.serializeUser);
  passport.deserializeUser(passportManager.deserializeUser);

  return passport;
};
