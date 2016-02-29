module.exports = function initSocketIo(libs) {
  libs.server = require('http').Server(libs.app);
  libs.io = require('socket.io')(libs.server);
};
