import React from "react";

const PatternSelection = ({ handlePatternClick }) => {
  const patterns = [
    {
      name: "Pattern 1",
      description: "Our most loved pattern.",
      image: "/pattern1.jpg",
    },
    {
      name: "Pattern 2",
      description: "Beloved by all, this is our finest pattern.",
      image: "/pattern1.jpg",
    },
    {
      name: "Pattern 3",
      description: "If you appreciate simplicity, this pattern is for you.",
      image: "/pattern1.jpg",
    },
  ];

  return (
    <div>
      <h2>Select a Pattern to Download</h2>
      <div className="pattern-list">
        {patterns.map((pattern) => (
          <div key={pattern.name} className="pattern-item">
            <img
              src={pattern.image}
              alt={pattern.name}
              className="pattern-image"
              onClick={() => handlePatternClick(pattern.name)}
            />
            <div className="pattern-details">
              <div className="pattern-name">{pattern.name}</div>
              <div className="pattern-description">{pattern.description}</div>
              <button
                className="download-button"
                onClick={() => handlePatternClick(pattern.name)}
              >
                Download Pattern
              </button>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default PatternSelection;
