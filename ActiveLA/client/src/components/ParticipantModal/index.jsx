import React, { useState } from "react";
import Button from "react-bootstrap/Button";
import Accordion from "react-bootstrap/Accordion";
import AccordionBody from "react-bootstrap/esm/AccordionBody";
import Modal from "react-bootstrap/Modal";

function ParticipantModal(props) {

  const { attendees } = props;
  const [show, setShow] = useState(false);

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  return (
    <>
      <Button variant={attendees.length > 0 ? "primary" : "secondary"} onClick={handleShow} style={{margin: "auto"}} disabled={attendees.length <= 0}>
        Participants
      </Button>
      <Modal show={show} onHide={handleClose} size="lg">
        <Modal.Header closeButton>
          <Modal.Title> Participants </Modal.Title>
        </Modal.Header>
        <Modal.Body>
          {attendees.length > 0 ?
          <Accordion>
          {
            attendees.map((attendee) => {
              return (
                <Accordion.Item eventKey={attendee}>
                  <Accordion.Header>{attendee.name}</Accordion.Header>
                  <AccordionBody>
                    <p>About: {attendee.about}</p>
                    <p>Email: {attendee.email}</p>
                    <p>Pronouns: {attendee.pronouns}</p>
                  </AccordionBody>  
                </Accordion.Item>
              )
            })
          }
          </Accordion> :
          <h3 style={{textAlign: "center"}}>No participants for now</h3>
          }
        </Modal.Body>
      </Modal>
    </>
  )
}

export default ParticipantModal;