/* eslint no-nested-ternary: "off" */
import React, { useContext } from "react";
import Button from "react-bootstrap/esm/Button";
import Col from "react-bootstrap/Col";
import { useNavigate } from "react-router-dom";
import Row from "react-bootstrap/Row";
import { ProgressSpinner } from "primereact/progressspinner";
import HostingCard from "../hostingCard";
import PageStatus from "../../../../global/page-status";

function HostingEvents(props) {
  const { events } = props;
  const pageStatus = useContext(PageStatus);
  const navigate = useNavigate();

  return (
    <div
      style={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        flexGrow: 1,
      }}
    >
      {
      pageStatus.isLoading ? (
        <ProgressSpinner />
      ) : (
      events.length > 0 ? (
        <Row xs={1} md={4} className="g-4">
          { events.map((event) => (
            <Col>
              <HostingCard event={event} />
            </Col>
          ))}
        </Row>
        ) : (
        <div style={{display: "flex", flexDirection: "column", margin: "8rem auto 0 auto"}}>
          <h2> You host no events for now. </h2>
          <Button 
            style={{backgroundColor: "transparent", border: "none", color: "blue"}} 
            onClick={() => navigate("/post-event")}
          > Host one here
          </Button>
        </div>
      ))}
    </div>
  );
}

export default HostingEvents;
