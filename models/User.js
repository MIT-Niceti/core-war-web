const mongoose = require('../libs/mongoose');
const Schema = mongoose.Schema;

const userSchema = new Schema({
  name: {
    type: String,
    required: true,
  },
  password: {
    type: String,
    required: true,
  },
  email: {
    type: String,
    required: true,
  },
});

userSchema.plugin(mongoose.autoIncrement.plugin, { model: 'user', field: 'id' });

const userModel = mongoose.model('user', userSchema);

module.exports = userModel;
