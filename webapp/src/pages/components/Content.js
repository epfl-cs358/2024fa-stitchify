import React from "react";
import "./contentStyles.css";

function Content({ title, description, children }) {
  return (
    <div className="content-container">
      <h2 className="content-title">{title}</h2>

      {description && (
        <div
          className="page-description"
          dangerouslySetInnerHTML={{ __html: description }}
        />
      )}

      <div className="content-children">{children}</div>
    </div>
  );
}

export default Content;
