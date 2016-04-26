const conf = require('../config/app.config.json');

const mongoose = require('mongoose');
mongoose.autoIncrement = require('mongoose-auto-increment');

var url = '';
url += 'mongodb://';
url += conf.database.host;
url += ':' + conf.database.port;
url += '/' + conf.database.name;

const connection = mongoose.connect(url);

mongoose.autoIncrement.initialize(connection);

module.exports = mongoose;
