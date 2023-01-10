import React, { useState, useContext } from "react";
import { useNavigate } from "react-router-dom";
import Button from "react-bootstrap/Button";
import Form from "react-bootstrap/Form";
import bcrypt from "bcryptjs";
import InputGroup from "react-bootstrap/InputGroup";
import { Chip } from "primereact/chip";
import { createNewUser, getUserByEmail } from "../../services/index";
import FormLayout from "../../components/FormLayout";
import notify from "../../components/CustomToast";
import * as constants from "../../constants";
import AuthContext from "../../services/authContext";

function SignupForm() {
  const navigate = useNavigate();
  const [sportValue, setSportValue] = useState();
  const [levelValue, setLevelValue] = useState();
  const [sportsName, setSportsName] = useState(Object.keys(constants.SPORT_TO_LOCATIONS_MAPPING));
  const authContext = useContext(AuthContext);

  const [data, setData] = useState({
    username: "",
    email: "",
    name: "",
    pronouns: "",
    about: "",
    interests: [],
    password: "",
    confirmPassword: "",
  });

  const [formErrors, setError] = useState({
    confirmPassword: "",
  });

  const onInput = (e) => {
    const { id, value } = e.target;

    if (id === "password") {
      bcrypt
        .hash(value, 10)
        .then((hashedPassword) => {
          console.log(value);
          setData({
            ...data,
            password: hashedPassword,
          });
        })
        .catch(() => {
          console.log("Password was not hashed successfully");
        });
      return;
    }
    setData((prevState) => ({
      ...prevState,
      [id]: value,
    }));
  };

  const onFormSubmit = (e) => {
    e.preventDefault();

    bcrypt
      .compare(data.confirmPassword, data.password)
      .then((passwordCheck) => {
        if (passwordCheck) {
          createNewUser(data)
            .then((res) => {
              if (res.data.success) {
                notify("Account created successfully", "success");
                getUserByEmail(data.email)
                  .then((result) => {
                    authContext.setupSessionInfo(true, result.data.User._id);
                  })
                  .catch((getIDerror) => {
                    notify(`Failed to fetch object ID (${getIDerror.message})`, "error");
                  });
                navigate("/");
                setData({});
                setError({});
              }
            })
            .catch((err) => {
              notify(`Failed to create a new user (${err.message})`, "error");
            });
        } else {
          setError({
            confirmPassword: "Password does not match",
          });
          authContext.setupSessionInfo(false, "");
        }
      })
      .catch((bcrypytErr) => {
        notify(`Password failed to unhash/does not match (${bcrypytErr.message})`, "error");
      });
  };

  const updateInterest = (e) => {
    const { id, value } = e.target;
    if (id === "sport") {
      setSportValue(value);
    } else if (id === "level"){
      setLevelValue(value);
    }
  };

  const addInterest = () => {
    if(!sportValue || !levelValue)
      return;

    setData({
      ...data,
      interests: [...data.interests, { sport: sportValue, level: levelValue }],
    });
    const newSportsArray = sportsName.filter((remainingSport) => {
      return remainingSport !== sportValue;
    });
    setSportsName(newSportsArray);
    setSportValue();
  };

  const renderInterests = data.interests
    ? data.interests.map((interest) => {
        const { sport, level } = interest;
        const labelText = `${sport} (${level})`;
        return (
          <div style={{ marginLeft: "8px", marginTop: "10px", display: "inline-block" }}>
            <Chip
              label={labelText}
              removable // TODO: Fix remove button not showing
              onRemove={() => {
                const newInterestArray = data.interests.filter((remainingInterest) => {
                  return remainingInterest.sport !== sport;
                });
                setData({
                  ...data,
                  interests: newInterestArray,
                });
                console.log(newInterestArray);
              }}
            />
          </div>
        );
      })
    : null;

  return (
    <Form onSubmit={onFormSubmit}>
      <Form.Text className="text-muted">
        Have An Account?
        <Form.Text style={{ color: "blue", marginRight: "8px", marginLeft: "8px" }} onClick={() => navigate("/login")}>
          Sign in
        </Form.Text>
      </Form.Text>
      <Form.Group className="mb-2" controlId="username">
        <Form.Label>Username</Form.Label>
        <Form.Control type="text" autoFocus onChange={onInput} placeholder="Create username" required />
      </Form.Group>

      <Form.Group className="mb-2" controlId="email">
        <Form.Label>Email</Form.Label>
        <Form.Control type="email" onChange={onInput} placeholder="Enter a valid email" required />
      </Form.Group>

      <Form.Group className="mb-2" controlId="name">
        <Form.Label>Name</Form.Label>
        <Form.Control type="text" onChange={onInput} placeholder="Enter your name" required />
      </Form.Group>
      <Form.Group className="mb-2" controlId="pronouns">
        <Form.Label>Pronouns</Form.Label>
        <Form.Control as="select" onChange={onInput} placeholder="Select your pronouns">
          <option value="Do not wish to declare">Select your pronouns</option>
          <option value="He/Him">He/Him</option>
          <option value="She/Her">She/Her</option>
          <option value="They/Them">They/Them</option>
          <option value="Others">Others</option>
        </Form.Control>
      </Form.Group>

      <Form.Group className="mb-2" controlId="about">
        <Form.Label>About</Form.Label>
        <Form.Control
          type="textarea"
          placeholder="Give a short description about yourself"
          rows={3}
          onChange={onInput}
        />
      </Form.Group>

      <Form.Group className="mb-2">
        <Form.Label>Interests & Proficiency Level</Form.Label>
        <InputGroup>
          <Form.Select id="sport" onChange={updateInterest}>
            <option value="">Select Sport</option>
            {Object.keys(constants.SPORT_TO_LOCATIONS_MAPPING).map((sport) => (
              <option value={sport}>{sport}</option>
            ))}
          </Form.Select>
          <Form.Select id="level" onChange={updateInterest}>
            <option value="" >Select Skill Level</option>
            {constants.SKILL_LEVEL.map((proficiency) => (
              <option value={proficiency}>{proficiency}</option>
            ))}
          </Form.Select>
          <Button variant="light" onClick={addInterest}>
            Add
          </Button>
        </InputGroup>
        <div>{renderInterests}</div>
      </Form.Group>
      <Form.Group className="mb-2" controlId="password">
        <Form.Label>Create Password</Form.Label>
        <Form.Control type="password" onChange={onInput} placeholder="Create a password" required />
      </Form.Group>

      <Form.Group className="mb-2" controlId="confirmPassword">
        <Form.Label>Confirm Password</Form.Label>
        <Form.Control type="password" onChange={onInput} placeholder="Please re-enter password" required />
        {formErrors.confirmPassword && <p className="text-danger">{formErrors.confirmPassword}</p>}
      </Form.Group>

      <Button variant="primary" type="submit">
        Submit
      </Button>
    </Form>
  );
}

function SignUpPage() {
  return (
    <FormLayout>
      <SignupForm />
    </FormLayout>
  );
}

export default SignUpPage;
