#!/usr/bin/env nodemon

// Include application configuration file
const conf = require('./config/app.config.json');
conf.rootFolder = __dirname;

// Include and initialize node libraries
const libs = require('./libs')(conf);

// Load controllers
require('./controllers')(conf, libs);
