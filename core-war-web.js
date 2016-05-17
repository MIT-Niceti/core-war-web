#!/usr/bin/env nodemon

var cookieParser = require('cookie-parser');
var passportSocketIo = require('passport.socketio');

// Include application configuration file
const conf = require('./config/app.config.json');
conf.rootFolder = __dirname;

const app = require('./libs/express')(conf);

const server = app.listen(conf.http.port, function () {
  console.log('Http server listening on port ' + conf.http.port);
});

const io = require('socket.io')(server);

require('./routes')(app, conf, { io: io });
