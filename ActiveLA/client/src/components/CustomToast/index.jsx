/* eslint no-else-return: "warn" */
import { toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';

// Creates a toast rendered in a ToastContainer nested under dashboard-layout
const notify = (message, type) => {
  const options = {
    position: "bottom-left",
    autoClose: 3000,
    hideProgressBar: false,
    closeOnClick: false,
    pauseOnHover: false,
    draggable: false,
    progress: undefined
  }
  if (type === "success") {
    return toast.success(message, options);
  } else if (type === "info") {
    return toast.info(message, options);
  } else if (type === "warning") {
    return toast.warning(message, options);
  } else if (type === "error") {
    return toast.error(message, options);
  }
  return toast(message, options);
};

export default notify;