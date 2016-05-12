#!/usr/bin/env nodemon

var cookieParser = require('cookie-parser');
var passportSocketIo = require('passport.socketio');

// Include application configuration file
const conf = require('./config/app.config.json');
conf.rootFolder = __dirname;

const app = require('./libs/express')(conf);

function onAuthorizeSuccess(data, accept) {
  console.log('successful connection to socket.io');
  accept(null, true);
}

function onAuthorizeFail(data, message, error, accept) {
  if (error)
    throw new Error(message);
  console.log('failed connection to socket.io:', message);
  accept(null, false);
}

const server = app.listen(conf.http.port, function () {
  console.log('Http server listening on port ' + conf.http.port);
});

var io = require('socket.io')(server);
var libs = {};

/*io.use(passportSocketIo.authorize({
  cookieParser: cookieParser,
  key: 'sid',
  secret: 'trololo cat',
  store: app.store,
  success: onAuthorizeSuccess,
  fail: onAuthorizeFail,
}));*/
libs.io = io;
require('./routes')(app, conf, libs);
