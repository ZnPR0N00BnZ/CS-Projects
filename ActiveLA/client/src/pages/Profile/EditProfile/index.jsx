import React, { useState, useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import Button from "react-bootstrap/esm/Button";
import Card from "react-bootstrap/Card";
import ListGroup from "react-bootstrap/ListGroup";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import Form from "react-bootstrap/Form";
import InputGroup from "react-bootstrap/InputGroup";
import AuthContext from "../../../services/authContext";
import * as constants from "../../../constants";
import { getUserByID, updateUser } from "../../../services/index";

import PageLayout from "../../../components/PageLayout";
import notify from "../../../components/CustomToast";

function EditProfile() {
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
        setData(res.data.User);
        // interestArray = res.data.User.interests;
      })
      .catch((err) => console.log(err.message));
  }, []);

  // let interestArray = [];

  const onInput = (e) => {
    const { id, value } = e.target;
    setData((prevState) => ({
      ...prevState,
      [id]: value,
    }));
    console.log(data);
  };

  const [showInputGroup, setShowInputGroup] = useState(false);
  let newSport = "";
  let newLevel = "";

  const updateInterest = (e) => {
    const { id, value } = e.target;
    if (id === "newSport") {
      newSport = value;
    } else if (id === "newLevel") {
      newLevel = value;
    }
  };

  const removeInterest = (e) => {
    const newInterestArray = data.interests.filter((remainingInterest) => {
      return remainingInterest.sport !== e.sport;
    });
    setData({
      ...data,
      interests: newInterestArray,
    });
  };

  const addInterest = (e) => {
    setData({
      ...data,
      interests: [...data.interests, { sport: newSport, level: newLevel }],
    });
    setShowInputGroup(false);
  };

  const onFormSubmit = (e) => {
    e.preventDefault();
    updateUser(userID, data)
      .then((res) => {
        if (res.data.success) {
          notify("Profile updated successfully", "success");
          setData({});
          navigate("/profile");
        } else {
          notify("Did not manage to update profile", "warning");
        }
      })
      .catch((err) => {
        notify(err.message, "error");
      });
  };

  return (
    <PageLayout>
      <Card style={{ width: "60rem", marginLeft: "auto", marginRight: "auto" }}>
        <Form onSubmit={onFormSubmit}>
          <ListGroup variant="flush">
            <ListGroup.Item>
              <Row>
                <Col sm={3} style={{ fontWeight: "bold" }}>
                  Username
                </Col>
                <Col>
                  <Form.Group controlId="username">
                    <Form.Control type="text" onChange={onInput} defaultValue={data.username} required />
                  </Form.Group>
                </Col>
              </Row>
            </ListGroup.Item>
            <ListGroup.Item>
              <Row>
                <Col sm={3} style={{ fontWeight: "bold" }}>
                  Email
                </Col>
                <Col>
                  <Form.Group controlId="email">
                    <Form.Control type="email" onChange={onInput} defaultValue={data.email} required />
                  </Form.Group>
                </Col>
              </Row>
            </ListGroup.Item>
            <ListGroup.Item>
              <Row>
                <Col sm={3} style={{ fontWeight: "bold" }}>
                  Name
                </Col>
                <Col>
                  <Form.Group controlId="name">
                    <Form.Control type="name" onChange={onInput} defaultValue={data.name} required />
                  </Form.Group>
                </Col>
              </Row>
            </ListGroup.Item>
            <ListGroup.Item>
              <Row>
                <Col sm={3} style={{ fontWeight: "bold" }}>
                  Pronouns
                </Col>
                <Col>
                  <Form.Group controlId="pronouns">
                    <Form.Control as="select" onChange={onInput} defaultValue={data.pronouns}>
                      <option value="Do not wish to declare">Select your pronouns</option>
                      <option value="He/Him">He/Him</option>
                      <option value="She/Her">She/Her</option>
                      <option value="They/Them">They/Them</option>
                      <option value="Others">Others</option>
                    </Form.Control>
                  </Form.Group>
                </Col>
              </Row>
            </ListGroup.Item>
            <ListGroup.Item>
              <Row>
                <Col sm={3} style={{ fontWeight: "bold" }}>
                  About
                </Col>
                <Col>
                  <Form.Group controlId="about">
                    <Form.Control type="textarea" defaultValue={data.about} rows={3} onChange={onInput} />
                  </Form.Group>
                </Col>
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
                        <InputGroup>
                          <Form.Select id="sport" defaultValue={entry.sport} disabled>
                            <option>Select Sport</option>
                            {Object.keys(constants.SPORT_TO_LOCATIONS_MAPPING).map((sport) => (
                              <option value={sport}>{sport}</option>
                            ))}
                          </Form.Select>
                          <Form.Select id="level" defaultValue={entry.level} disabled>
                            <option>Select Skill Level</option>
                            {constants.SKILL_LEVEL.map((proficiency) => (
                              <option value={proficiency}>{proficiency}</option>
                            ))}
                          </Form.Select>
                          <Button variant="danger" onClick={() => removeInterest(entry)}>
                            Remove
                          </Button>
                        </InputGroup>
                      </Row>
                    );
                  })}
                  {showInputGroup ? (
                    <Row>
                      <InputGroup>
                        <Form.Select id="newSport" onChange={updateInterest}>
                          <option>Select Sport</option>
                          {Object.keys(constants.SPORT_TO_LOCATIONS_MAPPING).map((sport) => (
                            <option value={sport}>{sport}</option>
                          ))}
                        </Form.Select>
                        <Form.Select id="newLevel" onChange={updateInterest}>
                          <option>Select Skill Level</option>
                          {constants.SKILL_LEVEL.map((proficiency) => (
                            <option value={proficiency}>{proficiency}</option>
                          ))}
                        </Form.Select>
                        <Button variant="success" onClick={addInterest}>
                          Save
                        </Button>
                      </InputGroup>
                    </Row>
                  ) : null}
                  <Button variant="secondary" onClick={() => setShowInputGroup(true)}>
                    Add
                  </Button>
                </Col>
              </Row>
            </ListGroup.Item>
            <ListGroup.Item>
              <Button className="ms-2 btn btn-primary" variant="primary" type="submit">
                Submit
              </Button>
              <Button className="ms-2 btn btn-primary" variant="secondary" onClick={() => navigate("/profile")}>
                Cancel
              </Button>
            </ListGroup.Item>
          </ListGroup>
        </Form>
      </Card>
    </PageLayout>
  );
}

export default EditProfile;
