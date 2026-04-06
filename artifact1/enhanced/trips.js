/**
 * Trips Controller
 * Handles HTTP requests and delegates data operations to the service layer.
 */

const tripService = require("../services/tripService");

// GET: /trips - list all the trips
const tripsList = async (req, res, next) => {
  try {
    const trips = await tripService.getAllTrips();

    if (!trips || trips.length === 0) {
      const error = new Error("No trips found");
      error.status = 404;
      return next(error);
    }

    res.status(200).json(trips);
  } catch (err) {
    next(err);
  }
};

// GET: /trips/:tripCode - lists a single trip by code
const tripsFindByCode = async (req, res, next) => {
  try {
    const trip = await tripService.getTripByCode(req.params.tripCode);

    if (!trip) {
      const error = new Error("Trip not found");
      error.status = 404;
      return next(error);
    }

    return res.status(200).json(trip);
  } catch (err) {
    return next(err);
  }
};

// POST: /trips - Adds a new Trip
const tripsAddTrip = async (req, res, next) => {
  try {
    const savedTrip = await tripService.createTrip(req.body);
    return res.status(201).json(savedTrip);
  } catch (err) {
    err.status = 400;
    return next(err);
  }
};

// PUT: /trips/:tripCode - Updates an existing Trip
const tripsUpdateTrip = async (req, res, next) => {
  try {
    const updatedTrip = await tripService.updateTripByCode(
      req.params.tripCode,
      req.body,
    );

    if (!updatedTrip) {
      const error = new Error("Trip not found for update");
      error.status = 404;
      return next(error);
    }

    return res.status(200).json(updatedTrip);
  } catch (err) {
    err.status = err.status || 400;
    return next(err);
  }
};

module.exports = {
  tripsList,
  tripsFindByCode,
  tripsAddTrip,
  tripsUpdateTrip,
};
