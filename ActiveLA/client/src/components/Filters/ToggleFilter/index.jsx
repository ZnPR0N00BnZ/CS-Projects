import React from "react";
import ToggleButton from "react-bootstrap/ToggleButton";

function ToggleFilter(props) {
  const { checked, onToggle, name } = props;
  return (
    <ToggleButton
      id={name}
      type="checkbox"
      variant="secondary"
      checked={checked}
      onChange={(e) => {
        onToggle(e.currentTarget.checked);
      }}
    >
      {name}
    </ToggleButton>
  );
}

export default ToggleFilter;
