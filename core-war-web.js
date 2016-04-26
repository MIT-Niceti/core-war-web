#!/usr/bin/env nodemon

// Include application configuration file
const conf = require('./config/app.config.json');
conf.rootFolder = __dirname;

const app = require('./libs/express')(conf);
require('./routes')(app, conf);

const server = app.listen(conf.http.port, function () {
  console.log('Http server listening on port ' + conf.http.port);
});
