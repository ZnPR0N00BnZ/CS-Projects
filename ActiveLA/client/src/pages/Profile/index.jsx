import React, { useState, useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import Button from "react-bootstrap/esm/Button";
import Card from "react-bootstrap/Card";
import ListGroup from "react-bootstrap/ListGroup";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import AuthContext from "../../services/authContext";
import PageLayout from "../../components/PageLayout";
import { getUserByID } from "../../services/index";


function Profile() {
  const userID = useContext(AuthContext).user;
  const navigate = useNavigate();

  const [data, setData] = useState({
    username: "",
    email: "",
    name: "",
    pronouns: "",
    about: "",
    interests: [],
    password: "",
  });

  useEffect(() => {
    getUserByID(userID)
      .then((res) => {
        // const userData = new Map(Object.entries(res.data.User));
        // console.log(userData);
        setData(res.data.User);
      })
      .catch((err) => console.log(err.message));
  }, []);

  const editPressed = () => {
    navigate("/profile/edit-profile");
  };

  return (
    <PageLayout>
      <h1>{data.name}&apos;s Profile</h1>

      <Card style={{ width: "60rem", marginLeft: "auto", marginRight: "auto" }}>
        <ListGroup variant="flush">
          <ListGroup.Item>
            <Row>
              <Col sm={3} style={{ fontWeight: "bold" }}>
                Username
              </Col>
              <Col>{data.username}</Col>
            </Row>
          </ListGroup.Item>
          <ListGroup.Item>
            <Row>
              <Col sm={3} style={{ fontWeight: "bold" }}>
                Email
              </Col>
              <Col>{data.email}</Col>
            </Row>
          </ListGroup.Item>
          <ListGroup.Item>
            <Row>
              <Col sm={3} style={{ fontWeight: "bold" }}>
                Name
              </Col>
              <Col>{data.name}</Col>
            </Row>
          </ListGroup.Item>
          <ListGroup.Item>
            <Row>
              <Col sm={3} style={{ fontWeight: "bold" }}>
                Pronouns
              </Col>
              <Col>{data.pronouns}</Col>
            </Row>
          </ListGroup.Item>
          <ListGroup.Item>
            <Row>
              <Col sm={3} style={{ fontWeight: "bold" }}>
                About
              </Col>
              <Col>{data.about}</Col>
            </Row>
          </ListGroup.Item>
          <ListGroup.Item>
            <Row>
              <Col sm={3} style={{ fontWeight: "bold" }}>
                Interests
              </Col>
              <Col>
                {data.interests.map((entry) => {
                  return (
                    <Row>
                      <Col sm={3}>{entry.sport}</Col>
                      <Col style={{ fontStyle: "italic" }}>{entry.level}</Col>
                    </Row>
                  );
                })}
              </Col>
            </Row>
          </ListGroup.Item>
        </ListGroup>
        <Button variant="primary" onClick={editPressed}>
          Edit
        </Button>
      </Card>
    </PageLayout>
  );
}

export default Profile;
