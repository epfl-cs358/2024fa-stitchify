import React from "react";

function MenuItem({ label, isActive, onClick }) {
  return (
    <li className={isActive ? "active" : ""} onClick={onClick}>
      {label}
    </li>
  );
}

export default MenuItem;
