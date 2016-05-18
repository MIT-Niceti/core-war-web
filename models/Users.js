//
// Require database
const mongoose = require('../libs/mongoose');

//
// Init model dependancy
const ChampionsModel = require('./Champions');

//
// Describe user schema
const Schema = mongoose.Schema;
const usersSchema = new Schema({
  name: {
    type: String,
    required: true,
    unique: true,
  },
  password: {
    type: String,
    required: true,
    unique: false,
  },
  email: {
    type: String,
    required: true,
    unique: true,
  },
  selectedChampion: {
    type: Schema.Types.ObjectId,
    ref: 'champions',
  },
  champions: [{
      type: Schema.Types.ObjectId,
      ref: 'champions',
    },
  ],
  creationDate: {
    type: Date,
    default: Date.now,
    required: true,
    unique: false,
  },
});

//
// Init and export model
const usersModel = mongoose.model('users', usersSchema);

//
// Export model
module.exports = usersModel;
