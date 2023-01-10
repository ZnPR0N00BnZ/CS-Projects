/* eslint no-nested-ternary: "off" */

import React, { useState, useContext, useEffect } from "react";
import ListGroup from "react-bootstrap/ListGroup";
import { useNavigate } from "react-router-dom";
import Button from "react-bootstrap/Button";
import Modal from "react-bootstrap/Modal";
import ParticipantModel from "../../ParticipantModal";
import AuthContext from "../../../services/authContext";
import { checkIfRequested, getUserByID } from '../../../services'

function ModalMoreDetails(props) {
  const { event, requestJoinHandler, modalImageDisplay } = props;
  const { _id, name, date, time, location, ageGroup, playerNumber, costs, skillLevel, attending} = event;
  const authContext = useContext(AuthContext);
  const [show, setShow] = useState(false);
  const [pending, setPending] = useState(false);
  const [going, setGoing] = useState(false);
  const [attendees, setAttendees] = useState([]);
  
  const navigate = useNavigate();

  const hostID = event.host.id;
  const eid = _id;
  const uid = authContext.user;

  const getIfEventRequested = async () => {
    const res = await checkIfRequested(uid, eid);
    if (res.data.success){
      setPending(res.data.pending)
      setGoing(res.data.going)
    }
  }
  const getAttendees = async () => {
    attending.forEach(async (attendee) => {
      const res = await getUserByID(attendee);
      const user = res.data.User
      if (user){
        setAttendees((arr) => [
          ...arr,
          user
        ])
      }
    })
  }

  useEffect(() => {
    if (authContext.isLoggedIn){
      getIfEventRequested();
      getAttendees();
    }
    return (
      setAttendees([])
    )
  }, [event, authContext.user])

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  return (
    <>
      <div className="col text-center">
        <Button variant="outline-primary" onClick={handleShow}>
          Find Out More
        </Button>
      </div>
      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>{name}</Modal.Title>
        </Modal.Header>
        <img className="img-responsive" src={modalImageDisplay} alt="" />
        <Modal.Body>
          <ListGroup className="list-group-flush">
            <ListGroup.Item>Date: {date}</ListGroup.Item>
            <ListGroup.Item>Time: {time}</ListGroup.Item>
            <ListGroup.Item>Location: {location}</ListGroup.Item>
            <ListGroup.Item>Skill Level: {skillLevel}</ListGroup.Item>
            <ListGroup.Item>Age Group: {ageGroup}</ListGroup.Item>
            <ListGroup.Item>Attendees: {attending.length} / {playerNumber}</ListGroup.Item>
            <ListGroup.Item>Costs: {costs === undefined ? "None" : costs}</ListGroup.Item>
          </ListGroup>
        </Modal.Body>
        <Modal.Footer>
          <ParticipantModel attendees={attendees}/>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
          {
            uid === hostID ? 
              <p> You host this event </p> : 
            pending ?  
              <Button onClick={() => navigate('/my-events')}>
                Previously requested
              </Button> :
            going ?
              <Button onClick={() => navigate('/my-events')}>
                You are going
              </Button> :
            <Button variant="primary" onClick={() => requestJoinHandler(_id)}>
              Request to Join
            </Button>
          }
        </Modal.Footer>
      </Modal>
    </>
  );
}

export default ModalMoreDetails;
