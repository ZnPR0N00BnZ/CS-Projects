import { createContext } from "react";

export const AuthContext = createContext({
  setupSessionInfo: () => {},
  isLoggedIn: false,
  user: null,
});

export default AuthContext;
