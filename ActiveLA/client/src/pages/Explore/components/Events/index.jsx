import React, { useContext } from "react";
import Container from "react-bootstrap/esm/Container";
import Col from "react-bootstrap/Col";
import Row from "react-bootstrap/Row";
import { ProgressSpinner } from "primereact/progressspinner";
import EventCard from "../../../../components/EventCard";
import PageStatus from "../../../../global/page-status";

function Events(props) {
  const { events, requestJoinHandler } = props;
  const pageStatus = useContext(PageStatus);

  return (
    <div
      style={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        flexGrow: 1,
      }}
    >
      {pageStatus.isLoading ? (
        <ProgressSpinner />
      ) : (
        <Row xs={1} md={4} className="g-4">
          {events ? (
            events.map((event) => (
              <Col>
                <EventCard event={event} requestJoinHandler={requestJoinHandler} />
              </Col>
            ))
          ) : (
            <Container />
          )}
        </Row>
      )}
    </div>
  );
}

export default Events;
