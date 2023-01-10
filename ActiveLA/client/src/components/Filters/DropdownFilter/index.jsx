import Dropdown from "react-bootstrap/Dropdown";
import React from "react";

function DropdownFilter(props) {
  const { options, name, onSelect } = props;
  return (
    <div>
      <Dropdown onSelect={(eventKey) => onSelect(eventKey)}>
        <Dropdown.Toggle variant="success" id="dropdown-basic">
          {name}
        </Dropdown.Toggle>
        <Dropdown.Menu>
          {options.map((option) => (
            <Dropdown.Item key={option} eventKey={option}>
              {option}
            </Dropdown.Item>
          ))}
        </Dropdown.Menu>
      </Dropdown>
    </div>
  );
}

export default DropdownFilter;
