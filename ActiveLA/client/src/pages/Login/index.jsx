/* eslint no-underscore-dangle: 0 */
import React, { useState, useContext } from "react";
import { useNavigate } from 'react-router-dom';
import Button from "react-bootstrap/Button";
import Form from "react-bootstrap/Form";
import Col from "react-bootstrap/esm/Col";
import Container from "react-bootstrap/esm/Container";
import bcrypt from "bcryptjs";
import FormLayout from "../../components/FormLayout";
import { getUserByEmail } from "../../services/index";
import AuthContext from "../../services/authContext";
import notify from "../../components/CustomToast";

function LoginForm() {
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
              notify("Login successful!", "success")
              setData({});
              navigate('/')
            } else {
              setError({
                ...formErrors,
                password: "Wrong password!",
              });
              authContext.setupSessionInfo(false, "");
            }
          })
          .catch((err) => {
            console.log(err.message)

          });
      })
      .catch((err) => {
        setError({
          ...formErrors,
          email: "Email does not exist!",
        });
      });
  };

  return (
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
      <Container style={{ display: "flex", flexDirection: "column", marginBottom: "8px", marginLeft: "-12px" }}>
        <Form.Text className="text-muted">
          Forgot your password?
          <Form.Text style={{ color: "blue", marginRight: "8px", marginLeft: "8px" }} onClick={() => navigate("/signup")}>
            Reset.
          </Form.Text>
        </Form.Text>
        <Form.Text className="text-muted">
          No Account?
          <Form.Text style={{ color: "blue", marginRight: "8px", marginLeft: "8px" }} onClick={() => navigate("/signup")}>
            Sign up
          </Form.Text>
        </Form.Text>
      </Container>
      <Form.Group>
        <Button variant="primary" type="submit">
          Submit
        </Button>
      </Form.Group>
    </Form>
  );
}

function LoginPage() {
  return (
    <FormLayout>
      <LoginForm />
    </FormLayout>
  )
}

export default LoginPage;