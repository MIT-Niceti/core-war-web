//
// Require database
const mongoose = require('../libs/mongoose');

//
// Describe user schema
const Schema = mongoose.Schema;

const lobbySchema = new Schema({
  name: {
    type: String,
    required: true,
    unique: true,
  },
  creator: {
    type: Schema.Types.ObjectId,
    required: true,
  },
  members: {
    type: [Schema.Types.ObjectId],
    required: true,
  },
  maxPlayers: {
    type: Number,
    required: true,
  },
});

//
// Init and export model
const lobbiesModel = mongoose.model('lobbies', lobbySchema);

//
// Export model
module.exports = lobbiesModel;
