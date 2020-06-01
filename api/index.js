var express = require('express');
var r       = express.Router();


const service = require('./resources/service');

r.get('/service/create/:collection/:name/:status/:value', service.create);

r.get('/service/show/:collection', service.show);

module.exports = r;
