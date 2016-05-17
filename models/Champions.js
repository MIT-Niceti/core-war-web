//
// Require database
const mongoose = require('../libs/mongoose');

//
// Describe user schema
const Schema = mongoose.Schema;
const championsSchema = new Schema({
  name: {
    type: String,
    required: true,
    unique: false,
  },
  path: {
    type: String,
    required: true,
    unique: true,
  },
  creationDate: {
    type: Date,
    default: Date.now,
    required: true,
    unique: false,
  },
});

//
// Init and export model
const championsModel = mongoose.model('champions', championsSchema);

//
// Export model
module.exports = championsModel;
