var express = require('express');
var r       = express.Router();

const s = require("./resources/service");
r.get(
    '/service/create/:collection/:name/:status/:value',
    s.create
)
//http://localhost:3000/api/service/create/sensors/DHT-11/EN/78

r.get(
    '/service/show/:collection',
    s.show
)
// http://localhost:3000/api/service/show

module.exports = r;
