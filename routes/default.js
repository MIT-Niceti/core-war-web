const express = require('express');

module.exports = function initHttpRoutes(app, conf) {
  //
  //// GET requests

  // Serve static files
  app.use(express.static(conf.rootFolder + '/public'));

  // Redirect to main page
  app.get('/',
    function (req, res) {
      res.redirect('/index.html');
    }
  );
};
