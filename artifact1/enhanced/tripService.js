/**
 * Trip Service
 * Handles all database operations related to trips.
 * Separates data access logic from controllers for better maintainability.
 */

const mongoose = require("mongoose");
require("../models/travlr");

const Trip = mongoose.model("trips");

const getAllTrips = async () => {
  return Trip.find({}).exec();
};

const getTripByCode = async (tripCode) => {
  return Trip.findOne({ code: tripCode }).exec();
};

const createTrip = async (tripData) => {
  const newTrip = new Trip({
    code: tripData.code,
    name: tripData.name,
    length: tripData.length,
    start: tripData.start,
    resort: tripData.resort,
    perPerson: tripData.perPerson,
    image: tripData.image,
    description: tripData.description,
  });

  return newTrip.save();
};

const updateTripByCode = async (tripCode, tripData) => {
  return Trip.findOneAndUpdate(
    { code: tripCode },
    {
      code: tripData.code,
      name: tripData.name,
      length: tripData.length,
      start: tripData.start,
      resort: tripData.resort,
      perPerson: tripData.perPerson,
      image: tripData.image,
      description: tripData.description,
    },
    {
      new: true,
      runValidators: true,
    },
  ).exec();
};

module.exports = {
  getAllTrips,
  getTripByCode,
  createTrip,
  updateTripByCode,
};
