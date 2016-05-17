const fileUpload = require('express-fileupload');

module.exports = function (app) {
  app.use(fileUpload());
};
