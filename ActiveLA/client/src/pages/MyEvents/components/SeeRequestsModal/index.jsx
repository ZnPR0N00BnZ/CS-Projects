import React, { useState } from "react";
import Button from "react-bootstrap/Button";
import Modal from "react-bootstrap/Modal";

import PersonDetails from "../SeeRequestsPersonDetails";

function SeeRequestsModal(props) {
  const { event } = props;
  const [show, setShow] = useState(false);

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  return (
    <>
      <Button variant={event.pendingAccept.length > 0 ? "primary" : "secondary"} onClick={handleShow} style={{marginLeft: "0.5rem"}} disabled={event.pendingAccept.length <= 0}>
        See Requests
      </Button>{" "}
      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Join Requests</Modal.Title>
        </Modal.Header>
        <PersonDetails handleClose={handleClose} event={event} />
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>
    </>
  );
}

export default SeeRequestsModal;
