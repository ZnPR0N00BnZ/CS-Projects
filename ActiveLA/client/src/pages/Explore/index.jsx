import React, { useEffect, useState, useContext } from "react";
import { useNavigate } from "react-router-dom";
import PageLayout from "../../components/PageLayout";
import ExploreFilter from "./components/ExploreFilter";
import Events from "./components/Events";
import useIsFirstRender from "../../hooks/useIsFirstRender";
import AuthContext from "../../services/authContext";
import PageStatus from "../../global/page-status";

import { getAllEvents, getUserByID, requestToJoinEvent } from "../../services";
import notify from "../../components/CustomToast";

function Explore() {
  const navigate = useNavigate();

  const [filters, setFilters] = useState({});
  const [events, setEvents] = useState([]);
  const [filterChangeObserver, setFilterChangeObserver] = useState(0);

  const authContext = useContext(AuthContext);
  const pageStatus = useContext(PageStatus);
  const uid = authContext.user;
  const [name, setName] = useState();

  useEffect(() => {
    if (!uid) {
      return;
    }
    getUserByID(uid)
      .then((res) => {
        setName(res.data.User.name);
      })
      .catch((err) => {
        console.log(err);
      });
  }, [uid]);

  const updateEventsOnFilterChange = async () => {
    pageStatus.updatePageStatus(true);
    const fetchedEvents = await getAllEvents(filters);
    setEvents(fetchedEvents);
    pageStatus.updatePageStatus(false);
  };

  const firstRender = useIsFirstRender();

  useEffect(() => {
    if (!firstRender) {
      updateEventsOnFilterChange();
    }
  }, [filterChangeObserver]);

  const requestJoinHandler = async (eid) => {
    if (!authContext.isLoggedIn) {
      navigate("/login");
      notify("Login required", "error");
      return null;
    }
    notify("Request to join sent!", "success");
    const res = await requestToJoinEvent(uid, eid);
    navigate("/my-events");
    return res;
  };

  return (
    <PageLayout>
      <h2>Welcome {uid && authContext.isLoggedIn ? name : "to ActiveLA"} 👋</h2>
      <p className="mt-4">Discover Events</p>
      <p
        style={{
          display: "flex",
        }}
      >
        <ExploreFilter
          onChange={(exploreFilter) => {
            setFilters(exploreFilter);
            setFilterChangeObserver((prevObserver) => prevObserver + 1);
          }}
        />
      </p>
      <Events events={events} requestJoinHandler={requestJoinHandler} />
    </PageLayout>
  );
}

export default Explore;
