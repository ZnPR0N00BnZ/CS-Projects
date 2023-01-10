// Example model for a Todo object

import mongoose from "mongoose";

// Create new mongoose schema object
const Schema = mongoose.Schema;
let Event = new Schema(
  {
    // List attributes model will contain. They will correspond to attribute name in MongoDB
    name: {
      type: String,
    },
    date: {
      type: String,
    },
    time: {
      type: String,
    },
    location: {
      type: String,
    },
    ageGroup: {
      type: String, // Open
    },
    playerNumber: { // TODO: What is this exactly and can we possibly use len of one of its refs
        type: String
    },
    costs: {
      type: String, // toggle
    },
    skillLevel: {
      type: String, // Beginner, Intermediate, Advanced
    },
    host: {
      type: Schema.Types.ObjectId,
      ref: "User",
    },
    pendingAccept: [
      {
        type: Schema.Types.ObjectId,
        ref: "User",
      },
    ],
    attending: [
      {
        type: Schema.Types.ObjectId,
        ref: "User",
      },
    ],
  },
  {
    toJSON: { virtuals: true }, // So `res.json()` and other `JSON.stringify()` functions include virtuals
    toObject: { virtuals: true }, // So `console.log()` and other functions that use `toObject()` include virtuals
  }
);

export default mongoose.model("Event", Event);
