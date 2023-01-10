import React, { useState } from "react";
import Button from "react-bootstrap/Button";
import Modal from "react-bootstrap/Modal";
import { useNavigate } from "react-router-dom";
import notify from "../../../../components/CustomToast";
import { deleteEvent } from "../../../../services";

function DeleteEventModal(props) {
  /* eventID will be passed down using props */
  const { eventID } = props;
  const [show, setShow] = useState(false);

  const navigate = useNavigate();

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  function handleDeleteEvent() {
    deleteEvent(eventID).then(
      (res) => {
        notify("Event deleted", "success");
        navigate(0);
      }).catch(
        (err) => {
          notify("Failed to delete event :(", "error");
        }
      );
  }

  return (
    <>
      <Button variant="danger" onClick={handleShow}>
        Delete Event
      </Button>
      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Are you sure?</Modal.Title>
        </Modal.Header>
        <Modal.Footer>
          <Button variant="danger" onClick={() => handleDeleteEvent()}>
            Confirm Delete
          </Button>
          <Button variant="secondary" onClick={handleClose}>
            I changed my mind
          </Button>
        </Modal.Footer>
      </Modal>
    </>
  );
}

export default DeleteEventModal;
