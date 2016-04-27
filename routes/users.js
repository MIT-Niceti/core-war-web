const ensureLoggedIn = require('../libs/connectEnsureLogin').ensureLoggedIn;
const ensureLoggedOut = require('../libs/connectEnsureLogin').ensureLoggedOut;

const usersController = require('../controllers/users');

module.exports = function initUsersRoutes(app, conf) {
  const passport = require('../libs/passport')(app);

  //
  //// GET requests

  // Users management
  app.get('/index.html',
    function (req, res) {
      res.render('index', { user: req.user });
    }
  );

  app.get('/user_profile.html',
    ensureLoggedIn('/index.html'),
    function (req, res) {
      usersController.retrieveUserProfile(req, res)
      .then(function (data) {
        res.render('user_profile', data);
      });
    }
  );

  app.get('/logout',
  ensureLoggedIn('/index.html'),
    function (req, res) {
      req.logout();
      req.session.save(function () {
        res.redirect('/index.html');
      });
    }
  );

  //
  //// POST requests

  // Users management
  app.post('/login',
  ensureLoggedOut('/index.html'),
    passport.authenticate('local', { failureRedirect: '/index.html' }),
    function (req, res) {
      req.session.save(function () {
        res.redirect('/index.html');
      });
    }
  );

  app.post('/sign-up',
  ensureLoggedOut('/index.html'),
    usersController.createUser({
      successRedirect: '/index.html',
      failureRedirect: '/index.html',
    })
  );

  app.post('/update_user_profile',
  ensureLoggedIn('/index.html'),
    usersController.updateUserProfile({
      successRedirect: '/user_profile.html',
      failureRedirect: '/user_profile.html',
    })
  );
};
