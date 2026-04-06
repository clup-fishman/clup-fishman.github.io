/**
 * Centralized Error Handler
 * Processes all application errors and returns appropriate responses
 * for both API routes and server-rendered views.
 */

function errorHandler(err, req, res, next) {
  console.error(err);

  const status = err.status || 500;
  const message = err.message || "Internal Server Error";

  if (req.originalUrl.startsWith("/api")) {
    return res.status(status).json({
      message: message,
    });
  }

  res.locals.message = message;
  res.locals.error = req.app.get("env") === "development" ? err : {};

  return res.status(status).render("error");
}

module.exports = errorHandler;
