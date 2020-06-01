var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');












var app = express();

// app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());







var indexRouter = require('./routes/index');
var apiRoutes   = require('./api/index');

//Pages HERE
app.use('/', indexRouter);
app.use('/api', apiRoutes);









app.use(express.static(path.join(__dirname, 'public')))
   .use(express.static(path.join(__dirname, 'modules/base/client/assets/js')))
   .use(express.static(path.join(__dirname, 'modules/users/client/assets/js')))
   .set('views', [
     path.join(__dirname, 'views'), //VIEW HERE
     path.join(__dirname, 'modules/base/client/views'),
     path.join(__dirname, 'modules/users/client/views')
   ])
   .engine('html', require('ejs').renderFile)
   .set('view engine', 'ejs');







// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});








// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;



///https://www.sitepoint.com/create-new-express-js-apps-with-express-generator/
