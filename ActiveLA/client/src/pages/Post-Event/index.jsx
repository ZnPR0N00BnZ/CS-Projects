import React, { useEffect, useState, useContext } from "react";
import Button from "react-bootstrap/Button";
import Col from "react-bootstrap/Col";
import Row from "react-bootstrap/Row";
import Form from "react-bootstrap/Form";
import Dropdown from "react-bootstrap/Dropdown";
import { useNavigate } from "react-router-dom";
import PageLayout from "../../components/PageLayout";
import { addEventService } from "../../services";
import AuthContext from "../../services/authContext";
import notify from "../../components/CustomToast";

function postEvent() {
  const navigate = useNavigate();
  const authContext = useContext(AuthContext);
  /* For number of players */
  const playerNumArray = [];
  const maxPlayerNum = 15;
  for (let x = 1; x <= maxPlayerNum; x += 1) {
    playerNumArray.push(x);
  }

  /* For Dropdown Menu */
  const [dropDown, setDropDown] = useState("Select a Number");
  const setDropDownFunc = (field) => {
    setDropDown(field);
  };
  const uid = authContext.user;
  const [form, setForm] = useState({ host: uid });
  const [errors, setErrors] = useState({});
  const setField = (field, value) => {
    setForm({
      ...form,
      [field]: value,
    });

    if (errors[field])
      setErrors({
        ...errors,
        [field]: null,
      });
  };

  const validateForm = () => {
    const { name, date, time, location, ageGroup, playerNumber, costs, skillLevel } = form;
    const newErrors = {};
    if (!name || name === "") newErrors.name = "Please enter your name";
    if (!date || date === "") newErrors.date = "Please enter date";
    if (!time || time === "") newErrors.time = "Please enter time";
    if (!location || location === "") newErrors.location = "Please enter location";
    if (!ageGroup || ageGroup === "") newErrors.ageGroup = "Please enter an age group";
    if (!playerNumber || playerNumber === "") newErrors.playerNumber = "Please enter player number";
    if (!skillLevel || skillLevel === "") newErrors.skillLevel = "Please enter skill level";

    return newErrors;
  };

  const handleSubmit = (e) => {
    e.preventDefault();

    const formErrors = validateForm();
    if (Object.keys(formErrors).length > 0) {
      console.log("error! Displaying form object");
      console.log(form);
      setErrors(formErrors);
    } else {
      addEventService(form)
        .then((res) => {
          notify("Successfully posted a new event!", "success");
          navigate("/my-events");
        })
        .catch((err) => console.log(err.message));
    }
  };

  const sportsNames = [
    { id: "1", sportsType: "Badminton" },
    { id: "2", sportsType: "Baseball" },
    { id: "3", sportsType: "Basketball" },
    { id: "4", sportsType: "Cricket" },
    { id: "5", sportsType: "Football" },
    { id: "6", sportsType: "Hockey" },
    { id: "7", sportsType: "Rugby" },
    { id: "8", sportsType: "Soccer" },
    { id: "9", sportsType: "Swimming" },
    { id: "10", sportsType: "Table Tennis" },
    { id: "11", sportsType: "Ultimate Frisbee" },
    { id: "12", sportsType: "Volleyball" },
  ];

  const sportsLocations = [
    { id: "1", sportsID: "Badminton", sportLocation: "Pardee Gym (Court 1)" },
    { id: "2", sportsID: "Badminton", sportLocation: "Pardee Gym (Court 2)" },
    { id: "3", sportsID: "Badminton", sportLocation: "Pardee Gym (Court 3)" },
    { id: "4", sportsID: "Badminton", sportLocation: "Pardee Gym (Court 4)" },
    { id: "5", sportsID: "Badminton", sportLocation: "Students Activities Center Hall (Court 1)" },
    { id: "6", sportsID: "Badminton", sportLocation: "Students Activities Center Hall (Court 2)" },
    { id: "7", sportsID: "Baseball", sportLocation: "Easton Stadium" },
    { id: "8", sportsID: "Baseball", sportLocation: "Jackie Robinson Stadium" },
    { id: "9", sportsID: "Basketball", sportLocation: "Collins Court (Court 1)" },
    { id: "10", sportsID: "Basketball", sportLocation: "Collins Court (Court 2)" },
    { id: "11", sportsID: "Basketball", sportLocation: "Collins Court (Court 3)" },
    { id: "12", sportsID: "Basketball", sportLocation: "Hitch Basketball Courts (Court 1)" },
    { id: "13", sportsID: "Basketball", sportLocation: "Hitch Basketball Courts (Court 2)" },
    { id: "14", sportsID: "Cricket", sportLocation: "El Monte Cricket Field 1" },
    { id: "15", sportsID: "Cricket", sportLocation: "El Monte Cricket Field 2" },
    { id: "16", sportsID: "Cricket", sportLocation: "Marder Cricket Field" },
    { id: "17", sportsID: "Cricket", sportLocation: "Severn Cricket Field" },
    { id: "18", sportsID: "Football", sportLocation: "Drake Stadium" },
    { id: "19", sportsID: "Football", sportLocation: "Spaulding Field" },
    { id: "20", sportsID: "Hockey", sportLocation: "Mar Vista Recreation Center" },
    { id: "21", sportsID: "Hockey", sportLocation: "North Athletic Field" },
    { id: "22", sportsID: "Rugby", sportLocation: "North Athletic Field" },
    { id: "23", sportsID: "Rugby", sportLocation: "Sullivan Field" },
    { id: "24", sportsID: "Soccer", sportLocation: "Intramural Field (Court 1)" },
    { id: "25", sportsID: "Soccer", sportLocation: "Intramural Field (Court 2)" },
    { id: "26", sportsID: "Soccer", sportLocation: "Intramural Field (Court 3)" },
    { id: "27", sportsID: "Soccer", sportLocation: "Walls Annenberg Stadium" },
    { id: "28", sportsID: "Swimming", sportLocation: "Speiker Aquatic Center (Lane 1)" },
    { id: "29", sportsID: "Swimming", sportLocation: "Speiker Aquatic Center (Lane 2)" },
    { id: "30", sportsID: "Swimming", sportLocation: "Speiker Aquatic Center (Lane 3)" },
    { id: "31", sportsID: "Swimming", sportLocation: "Speiker Aquatic Center (Lane 4)" },
    { id: "32", sportsID: "Swimming", sportLocation: "Speiker Aquatic Center (Lane 5)" },
    { id: "33", sportsID: "Swimming", sportLocation: "Speiker Aquatic Center (Lane 6)" },
    { id: "34", sportsID: "Table Tennis", sportLocation: "Pardee Gym (Table 1)" },
    { id: "35", sportsID: "Table Tennis", sportLocation: "Pardee Gym (Table 2)" },
    { id: "36", sportsID: "Table Tennis", sportLocation: "Pardee Gym (Table 3)" },
    { id: "37", sportsID: "Ultimate Frisbee", sportLocation: "Intramural Field (Court 1)" },
    { id: "38", sportsID: "Ultimate Frisbee", sportLocation: "Intramural Field (Court 2)" },
    { id: "39", sportsID: "Ultimate Frisbee", sportLocation: "Intramural Field (Court 3)" },
    { id: "40", sportsID: "Volleyball", sportLocation: "Pardee Gym (Court 1)" },
    { id: "41", sportsID: "Volleyball", sportLocation: "Pardee Gym (Court 2)" },
    { id: "42", sportsID: "Volleyball", sportLocation: "Students Activities Center Hall (Court 1)" },
    { id: "43", sportsID: "Volleyball", sportLocation: "Students Activities Center Hall (Court 2)" },
  ];

  const [sport, setSport] = useState([]);
  const [location, setLocation] = useState([]);

  useEffect(() => {
    setSport(sportsNames);
  }, []);

  const handleSport = (id) => {
    const dt = sportsLocations.filter((x) => x.sportsID === id);
    setLocation(dt);
  };

  return (
    <PageLayout>
      <h2>Host An Event!</h2>

      <Form>
        <Form.Group className="mb-3" controlId="name">
          <Form.Label>Sport: </Form.Label>
          <Form.Select
            id="selectSport"
            type="text"
            placeholder="eg. Basketball"
            value={form.name}
            onChange={(e) => {
              setField("name", e.target.value);
              handleSport(e.target.value);
            }}
            isInvalid={!!errors.name}
          >
            <option value="" selected disabled>
              -- Select a Sport --
            </option>
            {sport.map((spt) => {
              return (
                <option key={spt.id} value={spt.sportsType}>
                  {spt.sportsType}
                </option>
              );
            })}
          </Form.Select>
          <Form.Control.Feedback type="invalid">{errors.name}</Form.Control.Feedback>
        </Form.Group>
        <Row>
          <Form.Group as={Col} className="mb-3" controlId="date">
            <Form.Label>Date: </Form.Label>
            <Form.Control
              type="date"
              placeholder="eg. 10/24/2022"
              value={form.date}
              onChange={(e) => setField("date", e.target.value)}
              isInvalid={!!errors.date}
            />
            <Form.Control.Feedback type="invalid">{errors.date}</Form.Control.Feedback>
          </Form.Group>

          <Form.Group as={Col} className="mb-3" controlId="time">
            <Form.Label>Time:</Form.Label>
            <Form.Control
              type="time"
              placeholder="eg. 2:00pm"
              value={form.time}
              onChange={(e) => setField("time", e.target.value)}
              isInvalid={!!errors.time}
            />
            <Form.Control.Feedback type="invalid">{errors.time}</Form.Control.Feedback>
          </Form.Group>
        </Row>
        <Form.Group className="mb-3" controlId="location">
          <Form.Label>Location:</Form.Label>
          <Form.Select
            id="selectLocation"
            type="text"
            value={form.location}
            onChange={(e) => {
              setField("location", e.target.value);
            }}
            isInvalid={!!errors.location}
          >
            <option value="" selected disabled>
              -- Select a Location --
            </option>
            {location.map((loc) => {
              return <option value={loc.sportLocation}>{loc.sportLocation}</option>;
            })}
          </Form.Select>
          <Form.Control.Feedback type="invalid">{errors.location}</Form.Control.Feedback>
        </Form.Group>

        <Form.Group className="mb-3" controlId="ageGroup">
          <Form.Label>Age Group: </Form.Label>
          <Form.Select
            type="text"
            value={form.ageGroup}
            onChange={(e) => setField("ageGroup", e.target.value)}
            isInvalid={!!errors.ageGroup}
          >
            <option value="" selected disabled>
              -- Age Group --
            </option>
            <option value="Open to All Ages">Open to All Ages</option>
            <option value="Teens">Teens</option>
            <option value="Adults">Adults</option>
            <option value="Seniors">Seniors</option>
          </Form.Select>
          <Form.Control.Feedback type="invalid">{errors.ageGroup}</Form.Control.Feedback>
        </Form.Group>

        {/* <Form.Group className="mb-3" controlId="playerNumber">
          <Form.Label>Number of Player to look for</Form.Label>
          <Form.Control
            type="text"
            placeholder="eg 5"
            value={form.playerNumber}
            onChange={(e) => setField("playerNumber", e.target.value)}
            isInvalid={!!errors.playerNumber}
          />
          <Form.Control.Feedback type="invalid">{errors.playerNumber}</Form.Control.Feedback>
        </Form.Group> */}

        <Form.Group className="mb-3" controlId="costs">
          <Form.Label>Cost:</Form.Label>
          <Form.Control
            type="text"
            placeholder="None / eg. $10"
            value={form.costs}
            onChange={(e) => setField("costs", e.target.value)}
            isInvalid={!!errors.costs}
          />
          <Form.Control.Feedback type="invalid">{errors.costs}</Form.Control.Feedback>
        </Form.Group>

        <Row classname="mb-3">
          <Form.Group as={Col} className="mb-3" id="Dropdown">
            <Form.Label>Number Of Players Looking For:</Form.Label>
            <Dropdown>
              <Dropdown.Toggle id="dropdown-button" variant="secondary">
                {dropDown}
              </Dropdown.Toggle>
              <Dropdown.Menu variant="dark">
                {playerNumArray.map((type) => (
                  <Dropdown.Item
                    href="#/action-1"
                    onClick={(e) => {
                      setDropDownFunc(type);
                      setField("playerNumber", `${type}`);
                      /* update button title */
                    }}
                  >
                    {type}
                  </Dropdown.Item>
                ))}
              </Dropdown.Menu>
            </Dropdown>
          </Form.Group>

          <Form.Group as={Col} className="mt-5" id="skillLevel">
            {["radio"].map((type) => (
              <div key={`inline-${type}`} className="mb-3">
                <Form.Label style={{ paddingRight: "10px" }}>Skill Level: </Form.Label>
                <Form.Check
                  inline
                  label="Beginner"
                  name="group1"
                  onChange={(e) => setField("skillLevel", "Beginner")}
                  type={type}
                  id="skillLevel-Beginner"
                  isInvalid={!!errors.skillLevel}
                />
                <Form.Check
                  inline
                  label="Intermediate"
                  name="group1"
                  onChange={(e) => setField("skillLevel", "Intermediate")}
                  type={type}
                  id="skillLevel-Intermediate"
                  isInvalid={!!errors.skillLevel}
                />
                <Form.Check
                  inline
                  label="Advanced"
                  name="group1"
                  onChange={(e) => setField("skillLevel", "Advanced")}
                  type={type}
                  id="skillLevel-Advanced"
                  isInvalid={!!errors.skillLevel} /* Display error message? */
                />
              </div>
            ))}
          </Form.Group>
        </Row>
        {/* <Form.Group className="mb-3" controlId="skillLevel">
          <Form.Label>Skill Level</Form.Label>
          <Form.Control
            type="text"
            placeholder="eg Beginner/Intermediate/Advanced"
            value={form.skillLevel} 
            onChange={(e) => setField("skillLevel", e.target.value)}
            isInvalid={!!errors.skillLevel}
          />
          <Form.Control.Feedback type="invalid">{errors.skillLevel}</Form.Control.Feedback>
        </Form.Group> */}

        <Button variant="primary" type="submit" onClick={handleSubmit}>
          Submit
        </Button>
      </Form>
    </PageLayout>
  );
}

export default postEvent;
