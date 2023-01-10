import React, {useState} from "react";
import Container from "react-bootstrap/esm/Container";
import Header from "../Header";

function PageLayout(props) {
  const { children } = props;

  return (
    <>
      <Header />
      <Container className="mt-3 px-6">{children}</Container>
    </>
  );
}

export default PageLayout;
