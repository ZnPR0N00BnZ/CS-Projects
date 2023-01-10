/*
    ExpressJS server for ActiveLA. 
    Most things here should be set up. 
    Most development should be done under routes.js and the controllers folder.

    https://medium.com/fbdevclagos/setting-up-your-development-environment-96a6858ed5bb
*/
import apiRoutes from './routes.js';
import express from 'express';
import bodyParser from 'body-parser';
import cors from 'cors';
import mongoose from 'mongoose';
import dotenv  from "dotenv";

dotenv.config() // allows adding of environment variables in .env file

const app = express();
const MONGO_URI = process.env.MONGO_URI;
const PORT = 8080;

app.use(cors({
    origin: 'http://localhost:3000'
  }));
app.use(express.json()); // Parses request bodies
app.use(bodyParser.urlencoded({extended: false}))

// This sets up all the API routes in routes.js.
// All routes will be prefixed with /api.
app.use("/api", apiRoutes)

// Connecting to MongoDB
mongoose.connect(
    `${MONGO_URI}`, { 
    useNewUrlParser: true
});

const connection = mongoose.connection;
connection.once('open', () => {
    console.log("MongoDB database connection established successfully");
})

app.listen(PORT, function() {
    console.log("Server is running on Port: " + 8080);
});