import React from 'react'
import Button from 'react-bootstrap/esm/Button';
import Container from 'react-bootstrap/esm/Container';
import { useNavigate } from 'react-router-dom';

function FormLayout(props) {
  const { children } = props;
  const navigate = useNavigate();

  return (
    <>
      <Button style={{margin: "2rem 0 8rem 2rem", color: "black", backgroundColor: "white", border: "none"}} onClick={() => navigate('/')}>
        <h1>
          ActiveLA
        </h1>
      </Button>
      <Container style={{maxWidth: "48rem"}}>
        {children}
      </Container>
    </>
  )
}

export default FormLayout;