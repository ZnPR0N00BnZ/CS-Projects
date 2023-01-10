import React from "react";
import Card from "react-bootstrap/Card";
import ListGroup from "react-bootstrap/ListGroup";
import { Tooltip } from "primereact/tooltip";
import ModalMoreDetails from "./ModalMoreDetails";
import badmintonImage from "./images/badminton.jpg";
import tableTennisImage from "./images/tabletennis.jpg";
import volleyballImage from "./images/volleyball.jpg";
import swimmingImage from "./images/swimming.jpg";
import soccerImage from "./images/soccer.jpg";
import rugbyImage from "./images/rugby.jpg";
import hockeyImage from "./images/hockey.jpg";
import frisbeeImage from "./images/frisbee.jpg";
import footballImage from "./images/football.jpg";
import cricketImage from "./images/cricket.jpg";
import basketballImage from "./images/basketball.jpg";
import baseballImage from "./images/baseball.jpg";

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

function EventCard(props) {
  const { event, requestJoinHandler } = props;
  const sportsname = ImageDisplay(props);
  const host = event.host === undefined || event.host === null ? "" : event.host.name;
  const isOverflow = event.location.length > 20;

  return (
    <Card>
      <Card.Img variant="top" src={sportsname} />
      <Card.Body>
        <Card.Title>{event.name}</Card.Title>
        <ListGroup className="list-group-flush">
          <ListGroup.Item>Host: {host}</ListGroup.Item>
          <ListGroup.Item>Date: {event.date}</ListGroup.Item>
          <ListGroup.Item>Time: {event.time}</ListGroup.Item>
          <ListGroup.Item
            style={{
              display: "flex",
              maxWidth: "100%",
              alignItems: "center",
            }}
          >
            <div
              style={{
                marginRight: 5,
              }}
            >
              Location:
            </div>
            <Tooltip target=".is_overflow" />
            <div className={isOverflow ? "is_overflow text-truncate" : ""} data-pr-tooltip={event.location}>
              {event.location}
            </div>
          </ListGroup.Item>
          <ListGroup.Item>
            Attendees: {event.attending.length} / {event.playerNumber}
          </ListGroup.Item>
        </ListGroup>
        <ModalMoreDetails event={event} requestJoinHandler={requestJoinHandler} modalImageDisplay={sportsname} />
      </Card.Body>
    </Card>
  );
}

export default EventCard;
