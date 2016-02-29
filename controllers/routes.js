module.exports = function initHttpRoutes(conf, libs, managers) {
  const rootFolder = conf.rootFolder;
  const httpPort = conf.http.port;

  // Serve static files
  libs.app.use(libs.express.static(rootFolder + '/public'));

  // GET requests
  libs.app.get('/',
    function (req, res) {
      res.redirect('/index.html');
    }
  );

  libs.app.get('/index.html',
    function (req, res) {
      res.render('index', {});
    }
  );

  // Launch http server event loop
  libs.server.listen(httpPort, function () {
    console.log('Http server listening on port ' + httpPort);
  });
};
