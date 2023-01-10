// Model definition of a User

import mongoose from "mongoose";
const Schema = mongoose.Schema;

const User = new Schema(
  {
    // List attributes model will contain
    username: {
      type: String,
      required: true,
      unique: true,
    },
    email: {
      type: String,
      required: true,
      unique: true,
    },
    password: {
      type: String,
      required: true,
    },
    name: {
      type: String,
      required: true,
    },
    pronouns: {
      type: String,
    },
    about: {
      type: String,
    },
    interests: [
      {
        sport: String,
        level: String,
      },
    ],
    eventsHosting: [
      {
        type: Schema.Types.ObjectId,
        ref: "Event",
      },
    ],
    eventsGoing: [
      {
        type: Schema.Types.ObjectId,
        ref: "Event",
      },
    ],
    eventsPending: [
      {
        type: Schema.Types.ObjectId,
        ref: "Event",
      },
    ],
  },
  {
    toJSON: { virtuals: true }, // So `res.json()` and other `JSON.stringify()` functions include virtuals
    toObject: { virtuals: true }, // So `console.log()` and other functions that use `toObject()` include virtuals
  }
);

User.index({
  username: "text",
  name: "text",
});

export default mongoose.model("User", User);
