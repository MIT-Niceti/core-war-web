const conf = require('../config/app.config.json');

const mongoose = require('mongoose');

//
// Create url to connect to MondoDB
var url = '';
url += 'mongodb://';
url += conf.database.host;
url += ':' + conf.database.port;
url += '/' + conf.database.name;

mongoose.connect(url);

module.exports = mongoose;
