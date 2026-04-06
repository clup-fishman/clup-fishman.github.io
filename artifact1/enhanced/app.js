const createError = require("http-errors");
const express = require("express");
const path = require("path");
const cookieParser = require("cookie-parser");
const logger = require("morgan");
const errorHandler = require("./app_api/middleware/errorHandler");
require("./app_api/models/db");

// Define routers
const indexRouter = require("./app_server/routes/index");
const usersRouter = require("./app_server/routes/users");
const travelRouter = require("./app_server/routes/travel");
const apiRouter = require("./app_api/routes/index");
const aboutRouter = require("./app_server/routes/about");
const contactRouter = require("./app_server/routes/contact");
const mealsRouter = require("./app_server/routes/meals");
const newsRouter = require("./app_server/routes/news");
const roomsRouter = require("./app_server/routes/rooms");

const handlebars = require("hbs");

// Wire in auth module
const passport = require("passport");
require("./app_api/config/passport");

// dotenv
require("dotenv").config();

const app = express();

// view engine setup
app.set("views", path.join(__dirname, "app_server", "views"));

// register handlebars partials (https://www.npmjs.com/package/hbs)
handlebars.registerPartials(__dirname + "/app_server/views/partials");

app.set("view engine", "hbs");

app.use(logger("dev"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, "public")));
app.use(passport.initialize());

// Enable CORS
app.use("/api", (req, res, next) => {
  res.header("Access-Control-Allow-Origin", "http://localhost:4200");
  res.header(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept, Authorization",
  );
  res.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
  next();
});

// wire-up routes to controllers
app.use("/", indexRouter);
app.use("/users", usersRouter);
app.use("/travel", travelRouter);
app.use("/api", apiRouter);
app.use("/about", aboutRouter);
app.use("/contact", contactRouter);
app.use("/meals", mealsRouter);
app.use("/news", newsRouter);
app.use("/rooms", roomsRouter);

// catch 404 and forward to error handler
app.use(function (req, res, next) {
  next(createError(404));
});

// centralized error handler
app.use(errorHandler);

module.exports = app;
