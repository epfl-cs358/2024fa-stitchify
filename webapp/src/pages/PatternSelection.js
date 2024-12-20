import React, { useState } from "react";
import "./PatternSelection.css";

const PatternSelection = () => {
  const [sending, setSending] = useState(false);
  const [lastSentPattern, setLastSentPattern] = useState(null);

  const patterns = [
    {
      name: "Pattern 1",
      description: "Knitting a basic pattern under the user's supervision.",
      patternString: "knits 20",
    },
    {
      name: "Pattern 2",
      description: "Knitting a basic pattern without the user's supervision.",
      patternString: "knit 20",
    },
    {
      name: "Pattern 3",
      description: "Knitting a fancy pattern under the user's supervision.",
      patternString: "knitp 20",
    },
  ];

  const sendToWemos = async (patternString) => {
    console.log("Attempting to send pattern:", patternString);
    setSending(true);
    try {
      const apiUrl = `http://172.21.69.170/send`;
      console.log("Sending to URL:", apiUrl);

      const response = await fetch(apiUrl, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ item: patternString }),
      });

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      setLastSentPattern(patternString);
      console.log("Pattern sent successfully:", patternString);
    } catch (error) {
      console.error("Error sending pattern:", error);
    } finally {
      setSending(false);
    }
  };

  return (
    <div className="grid-container">
      <h2>Select a Pattern to Send</h2>

      {lastSentPattern && (
        <div className="last-sent">Last sent pattern: {lastSentPattern}</div>
      )}

      <div className="grid">
        {patterns.map((pattern) => (
          <div key={pattern.name} className="grid-cell">
            <h3>{pattern.name}</h3>
            <p>{pattern.description}</p>
            <button
              onClick={() => sendToWemos(pattern.patternString)}
              disabled={sending}
              className="download-btn"
            >
              {sending ? "Sending..." : "Send Pattern"}
            </button>
          </div>
        ))}
      </div>
    </div>
  );
};

export default PatternSelection;
