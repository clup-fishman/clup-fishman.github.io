/**
 * Trip Validation Middleware
 * Ensures required trip fields are present before processing requests.
 */

function validateTrip(req, res, next) {
  const { code, name, length, resort } = req.body;

  if (!code || !name || !length || !resort) {
    const error = new Error("Missing required trip fields");
    error.status = 400;
    return next(error);
  }

  next();
}

module.exports = validateTrip;
