import http from "./http-common";

// Events
export async function getAllEvents(filter) {
  try {
    const resp = await http.post(`/getAllEvents`, filter);
    const allEvents = resp.data.Event;
    return allEvents;
  } catch (error) {
    console.log(error.message);
    return [];
  }
}

export async function getRelatedEvents(uid) {
  try {
    const resp = await http.get(`/getRelatedEvents?uid=${uid}`);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function addEventService(form) {
  try {
    const resp = await http.post(`/addEvent`, form);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function updateEvent(eventID, updated){
  try {
    const resp = await http.put(`/updateEvent?_id=${eventID}`, updated)
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function updateUser(uid, updated){
  try {
    const resp = await http.put(`/updateUser?_id=${uid}`, updated)
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function deleteUser(uid){
  try {
    const resp = await http.delete(`/deleteUser?_id=${uid}`);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function deleteEvent(eventID){
  try {
    const resp = await http.delete(`/deleteEvent?_id=${eventID}`)
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}


export async function getInterestedUsers(eventID) {
  try {
    const resp = await http.get(`/getInterestedUsers?eid=${eventID}`);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

// User
export async function getUserByID (id) {
  try {
    const resp = await http.get(`/userByID?_id=${id}`);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function getUserByUsername (username) {
  try {
    const resp = await http.get(`/userByUsername?username=${username}`);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function getUserByEmail (email) {
  try {
    const resp = await http.get(`/userByEmail?email=${email}`);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function createNewUser (user) {
  try {
    const resp = await http.post(`/user`, user);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function acceptJoinRequest(uid, eventID) {
  try {
    const body = {
      "uid": uid,
      "eventID": eventID
    }
    const resp = await http.post(`/acceptJoinRequest`, body);
    return resp;
  } catch (err) {
    console.log(err.message);
    return err;
  }
}

export async function requestToJoinEvent(uid, eventID) {
  try {
    const body = {
      "uid": uid,
      "event": eventID
    }
    const resp = await http.post(`/requestToJoin`, body);
    return resp;
  } catch (error) {
    console.log(error.message);
    return error;
  }
}

export async function checkIfRequested(uid, eid) {
  try {
    const resp = await http.get(`/checkIfRequested?uid=${uid}&eid=${eid}`)
    return resp;
  } catch (error) {
    console.log(error.message);
    return error;
  }
}

export async function denyJoinRequest(uid, eid) {
  try {
    const body = {
      "uid": uid,
      "eventID": eid
    }
    const resp = await http.post('/denyJoinRequest', body);
    return resp;
  } catch (error) {
    console.log(error.message);
    return error;
  }
}