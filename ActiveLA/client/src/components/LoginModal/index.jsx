/* eslint no-underscore-dangle: 0 */

import React, { useState, useContext } from "react";
import { useNavigate } from "react-router-dom";
import Button from "react-bootstrap/Button";
import Modal from "react-bootstrap/Modal";
import Form from "react-bootstrap/Form";
import bcrypt from "bcryptjs";
import { getUserByEmail } from "../../services/index";
import AuthContext from "../../services/authContext";
import notify from "../CustomToast";

function LoginModal() {
  const [modalShow, setModalShow] = useState(false);
  const handleClose = () => setModalShow(false);
  const handleShow = () => setModalShow(true);
  const [data, setData] = useState({});
  const authContext = useContext(AuthContext);
  const navigate = useNavigate();

  const onInput = (e) => {
    const { id, value } = e.target;
    setData((prevState) => ({
      ...prevState,
      [id]: value,
    }));
  };

  const [formErrors, setError] = useState({
    email: "",
    password: "",
  });

  const onFormSubmit = (e) => {
    e.preventDefault();
    getUserByEmail(data.email)
      .then((res) => {
        setError({
          ...formErrors,
          email: "",
        });

        bcrypt
          .compare(data.password, res.data.User.password)
          .then((passwordCheck) => {
            if (passwordCheck) {
              authContext.setupSessionInfo(true, res.data.User._id);
              notify("Login successful!", "success");
              setData({});
              handleClose();
              navigate("/");
            } else {
              setError({
                ...formErrors,
                password: "Wrong password!",
              });
              authContext.setupSessionInfo(false, "");
            }
          })
          .catch((err) => {
            notify(`Password failed to unhash/does not match (${err.message})`, "error");
          });
      })
      .catch(() => {
        setError({
          ...formErrors,
          email: "Email does not exist!",
        });
      });
  };

  return (
    <>
      <Button
        style={{ fontWeight: "bold", color: "grey", backgroundColor: "transparent", border: "none" }}
        onClick={handleShow}
      >
        Login
      </Button>
      <Modal show={modalShow} onHide={handleClose} size="s" aria-labelledby="contained-modal-title-vcenter" centered>
        <Modal.Body>
          <Form onSubmit={onFormSubmit}>
            <h3>Login</h3>
            <Form.Group className="mb-3" controlId="email">
              <Form.Label>Email address</Form.Label>
              <Form.Control type="email" placeholder="Enter email" onChange={onInput} />
              {formErrors.email && <p className="text-danger">{formErrors.email}</p>}
            </Form.Group>
            <Form.Group className="mb-3" controlId="password">
              <Form.Label>Password</Form.Label>
              <Form.Control type="password" placeholder="Password" onChange={onInput} />
              {formErrors.password && <p className="text-danger">{formErrors.password}</p>}
            </Form.Group>
            <Form.Text className="text-muted">
              Forgot your password? Reset <a href="www.google.com">here</a>.
            </Form.Text>
            <Form.Group>
              <Button
                style={{
                  marginTop: 10,
                }}
                variant="primary"
                type="submit"
              >
                Submit
              </Button>
            </Form.Group>
          </Form>
        </Modal.Body>
      </Modal>
    </>
  );
}

export default LoginModal;
