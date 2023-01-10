import React, { useState, useEffect } from "react";
import Button from "react-bootstrap/Button";
import { useNavigate } from "react-router-dom";
import Accordion from "react-bootstrap/Accordion";
import AccordionBody from "react-bootstrap/esm/AccordionBody";
import { acceptJoinRequest, getUserByID, denyJoinRequest } from "../../../../services";
import notify from "../../../../components/CustomToast";

function PersonDetails(props) {
  const { event, handleClose } = props;
  const userIDs = event.pendingAccept;
  const eventID = event.id;
  const navigate = useNavigate();

  const [userList, setUserList] = useState([]);

  const generateUsers = async () => {
    const promises = [];
    for (let x = 0; x < userIDs.length; x += 1) {
      const id = userIDs[x];
      // fill promises array with promises
      promises.push(getUserByID(id));
    }
    // await all promises in array to become unprocessed data
    const unprocessedUsers = await Promise.all(promises);
    // process data in each slot
    const processedUsers = unprocessedUsers.map((value) => value.data.User);
    setUserList(processedUsers);
  };

  useEffect(() => {
    generateUsers();
  }, []);

  const handleDecline = async (uid) => {
    const resp = await denyJoinRequest(uid, eventID);
    if (resp.data.success) {
      notify("Declined join request", "success")
      handleClose()
      navigate(0)
      return;
    }
    notify("Failed to decline join request. Try again", "error")
  };

  const handleAccept = async (uid) => {
    const resp = await acceptJoinRequest(uid, eventID)
    if (resp.data.success){
      notify("Accepted join request", "success")
      handleClose();
      navigate(0)
      return;
    }
    notify("Failed to accept join request. Try again", "error")
  };

  return (
    <Accordion>
      {userList && (userList.length > 0) ? (
        userList.map((user) => (
          <Accordion.Item eventKey={user}>
            <Accordion.Header>{user.name}</Accordion.Header>
            <AccordionBody>
              <p>About: {user.about}</p>
              <p>Email: {user.email}</p>
              <p>Pronouns: {user.pronouns}</p>
              <Button variant="success" onClick={(e) => handleAccept(user.id)}>
                Accept
              </Button>{" "}
              <Button variant="danger" onClick={() => handleDecline(user.id)}>
                Decline
              </Button>
            </AccordionBody>
          </Accordion.Item>
        ))
      ) : (
        <h5 style={{textAlign: "center", margin: "3rem auto 3rem auto"}}>
          No requests for now
        </h5>
      )}
    </Accordion>
  );
}

export default PersonDetails;
