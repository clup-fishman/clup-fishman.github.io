const express = require("express");
const router = express.Router();

const validateTrip = require("../middleware/validateTrip");
const authenticateJWT = require("../middleware/authenticateJWT");
const tripsController = require("../controllers/trips");
const authController = require("../controllers/authentication");

router.route("/register").post(authController.register);

router.route("/login").post(authController.login);

router
  .route("/trips")
  .get(tripsController.tripsList)
  .post(authenticateJWT, validateTrip, tripsController.tripsAddTrip);

// Both methods require 'tripCode' parameter
router
  .route("/trips/:tripCode")
  .get(tripsController.tripsFindByCode)
  .put(authenticateJWT, validateTrip, tripsController.tripsUpdateTrip);

module.exports = router;
