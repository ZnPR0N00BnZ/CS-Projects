/* eslint-disable no-undef */
import bcrypt from "bcryptjs";
import notify from "../components/CustomToast";

// Utility functions that to interact with session storage &
// uses bcrypt to compare the hashed loginState

export function setLoginState(state) {
  return bcrypt
    .hash(state ? "true" : "false", 10)
    .then((hashedState) => {
      sessionStorage.setItem("loginState", hashedState);
    })
    .catch(() => {
      notify("loginState not hashed successfully", "error");
    });
}

export function getLoginState() {
  const loginState = sessionStorage.getItem("loginState");
  if (loginState) {
    const state = bcrypt.compareSync("true", loginState);
    return state;
  }
  return null;
}

export function setUserID(uid) {
  if (uid.length > 0) {
    sessionStorage.setItem("userID", uid);
  } else {
    sessionStorage.removeItem("userID");
  }
}

export function getUserID() {
  return sessionStorage.getItem("userID");
}
