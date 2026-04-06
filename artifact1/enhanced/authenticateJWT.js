/**
 * JWT Authentication Middleware
 * Validates JWT tokens and restricts access to protected routes.
 */

const jwt = require("jsonwebtoken");

const authenticateJWT = (req, res, next) => {
  const authHeader = req.headers["authorization"];

  if (!authHeader) {
    console.log("Authorization header missing");
    return res.sendStatus(401);
  }

  const token = authHeader.split(" ")[1];

  if (!token) {
    console.log("Bearer token missing");
    return res.status(401);
  }

  jwt.verify(token, process.env.JWT_SECRET, (err, decoded) => {
    if (err) {
      console.log("JWT verification failed");
      return res.status(401).json({
        message: "Token validation failed",
      });
    }

    req.auth = decoded;
    next();
  });
};

module.exports = authenticateJWT;
