module.exports = function initSequelize(libs, conf) {
  const dbConf = conf.database;

  libs.Sequelize = require('sequelize');
  libs.sequelize = new libs.Sequelize(dbConf.name, dbConf.username, dbConf.password, {
    host: dbConf.host,
    dialect: dbConf.dialect,
    pool: {
      max: 5,
      min: 0,
      idle: 10000,
    },
  });
};
