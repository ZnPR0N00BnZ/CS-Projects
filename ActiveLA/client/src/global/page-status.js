import { createContext } from "react";

export const PageStatus = createContext({
  updatePageStatus: (status) => {},
  isLoading: true,
});

export default PageStatus;
