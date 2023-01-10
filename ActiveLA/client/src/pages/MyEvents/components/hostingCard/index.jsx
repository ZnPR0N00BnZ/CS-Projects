import React, { useEffect, useState } from "react";
import Card from "react-bootstrap/Card";
import ListGroup from "react-bootstrap/ListGroup";
import badmintonImage from "../../../../components/EventCard/images/badminton.jpg";
import tableTennisImage from "../../../../components/EventCard/images/tabletennis.jpg";
import volleyballImage from "../../../../components/EventCard/images/volleyball.jpg";
import swimmingImage from "../../../../components/EventCard/images/swimming.jpg";
import soccerImage from "../../../../components/EventCard/images/soccer.jpg";
import rugbyImage from "../../../../components/EventCard/images/rugby.jpg";
import hockeyImage from "../../../../components/EventCard/images/hockey.jpg";
import frisbeeImage from "../../../../components/EventCard/images/frisbee.jpg";
import footballImage from "../../../../components/EventCard/images/football.jpg";
import cricketImage from "../../../../components/EventCard/images/cricket.jpg";
import basketballImage from "../../../../components/EventCard/images/basketball.jpg";
import baseballImage from "../../../../components/EventCard/images/baseball.jpg";
import DeleteEventModal from "../DeleteEventModal";
import SeeRequestsModal from "../SeeRequestsModal";
import ParticipantModal from "../../../../components/ParticipantModal";
import { getUserByID } from "../../../../services"

function ImageDisplay(props) {
  const { event } = props;
  switch (event.name) {
    case "Badminton":
      return badmintonImage;
    case "Table Tennis":
      return tableTennisImage;
    case "Volleyball":
      return volleyballImage;
    case "Swimming":
      return swimmingImage;
    case "Soccer":
      return soccerImage;
    case "Rugby":
      return rugbyImage;
    case "Hockey":
      return hockeyImage;
    case "Ultimate Frisbee":
      return frisbeeImage;
    case "Football":
      return footballImage;
    case "Cricket":
      return cricketImage;
    case "Basketball":
      return basketballImage;
    case "Baseball":
      return baseballImage;
    default:
      return badmintonImage;
  }
}

function HostingCard(props) {
  const { event } = props;
  const { _id, name, date, time, location, ageGroup, playerNumber, costs, skillLevel, attending } = event;
  const numberOfAttendees = attending.length;
  const sportsname = ImageDisplay(props);
  const host = event.host === undefined || event.host === null ? "" : event.host.name;

  const [attendees, setAttendees] = useState([])

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
    getAttendees()
    return (
      setAttendees([])
    )
  }, [event])

  return (
    <Card>
      <Card.Img variant="top" src={sportsname} />
      <Card.Title style={{marginTop: "8px"}}>{name}</Card.Title>
      <ListGroup className="list-group-flush">
        <ListGroup.Item>Host: {host}</ListGroup.Item>
        <ListGroup.Item>Date: {date}</ListGroup.Item>
        <ListGroup.Item>Time: {time}</ListGroup.Item>
        <ListGroup.Item>Location: {location}</ListGroup.Item>
        <ListGroup.Item>Skill Level: {skillLevel}</ListGroup.Item>
        <ListGroup.Item>Age Group: {ageGroup}</ListGroup.Item>
        <ListGroup.Item>Attendees: {numberOfAttendees} / {playerNumber}</ListGroup.Item>
        <ListGroup.Item>Costs: {costs === undefined ? "None" : costs}</ListGroup.Item>
      </ListGroup>
      <Card.Footer>
        <div style={{display: "flex", margin: "1rem 0 0.5rem 0", alignItems: "center", justifyContent: "center"}}>
          <DeleteEventModal eventID={_id} />
          <SeeRequestsModal event={event} />
        </div>
        <ParticipantModal attendees={attendees}/>
      </Card.Footer>
    </Card>
  );
}

export default HostingCard;
