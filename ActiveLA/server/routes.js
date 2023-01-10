import express from "express";
import { 
    findUserByID,
    findUserByUsername,
    findUserByEmail,
    addNewUser,
    requestToJoinEvent,
    getRelatedEvents,
    acceptJoinRequest,
    denyJoinRequest,
    deleteUser,
    updateUser,
    checkIfRequested
} from "./controllers/userController.js";

import {
    addEvent, 
    deleteEvent, 
    getAllEvents,
    getInterestedUsers,
    updateEvent
} from "./controllers/eventController.js"

const apiRoutes = express.Router();

// Users
apiRoutes.post('/user', addNewUser);
apiRoutes.get('/userByID', findUserByID); // Query param is _id
apiRoutes.get('/userByUsername', findUserByUsername); // Query param is username
apiRoutes.get('/userByEmail', findUserByEmail); // Query param is email
apiRoutes.put('/updateUser', updateUser); // Query param user _id, updated user in req body
apiRoutes.delete('/deleteUser', deleteUser); // Query param user _id

// Events
apiRoutes.post('/addEvent', addEvent); // New event to be added in req body
apiRoutes.post('/getallEvents', getAllEvents);
apiRoutes.get('/getRelatedEvents', getRelatedEvents); // Query param is user _id
apiRoutes.get('/getInterestedUsers', getInterestedUsers); // Query param is event _id
apiRoutes.put('/updateEvent', updateEvent); // Query param event _id, updated event in req body
apiRoutes.delete('/deleteEvent', deleteEvent); // Query param event _id

// Both
apiRoutes.post('/requestToJoin', requestToJoinEvent) // Body includes uid and eventID
apiRoutes.post('/acceptJoinRequest', acceptJoinRequest); // Body includes uid and eventID
apiRoutes.post('/denyJoinRequest', denyJoinRequest); // body takes in uid and eventID
apiRoutes.get('/checkIfRequested', checkIfRequested) // takes in params uid and eid

export default apiRoutes;
