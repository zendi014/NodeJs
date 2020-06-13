var express = require('express');
var r = express.Router();



// middleware function to check for logged-in users
var sessionChecker = (req, res, next) => {
  if (req.session.user && req.cookies.user_key) {
    next();
  } else {
    res.redirect('/');
  }
};


// const a = require('./resources/admin');
// r.get('/admin', sessionChecker, a.index);


r.get('/pages/:collection', function(req, res){
  data = {
      title: req.params.collection.toUpperCase(),
      name: 'SERVICE ',
  }
  res.render('./main/pages', data);
});

r.get('/socket/:collection', function(req, res){
  data = {
      title: req.params.collection.toUpperCase(),
      name: 'SERVICE ',
  }
  res.render('./main/socket_page', data);
});



module.exports = r;
