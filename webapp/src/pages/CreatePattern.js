import React, { useState, useEffect } from "react";
import Content from "./components/Content";
import "../createPatternStyles.css";

const getAction = (action, direction) => {
  if (action === "skip") {
    return direction === "right" ? "rs" : "ls";
  } else if (action === "take") {
    return direction === "right" ? "rt" : "lt";
  } else {
    return direction === "right" ? "fr" : "fl";
  }
};

const convertGridToPattern = (grid) => {
  const commands = [];
  let direction = "left";
  let commandString = "";

  grid.forEach((row) => {
    let prevAction = row[0] === 0 ? "take" : "skip";
    let count = 0;

    row.forEach((cell) => {
      const currentAction = cell === 0 ? "take" : "skip";
      if (currentAction === prevAction) {
        count += 1;
      } else {
        const command = `${getAction(prevAction, direction)} ${count}`;
        commands.push(command);
        commandString += command + ";";
        prevAction = currentAction;
        count = 1;
      }
    });

    const command = `${getAction(prevAction, direction)} ${count}`;
    commands.push(command);
    commandString += command + ";";

    const maxN = direction === "right" ? 2500 : -2500;
    const nCommand = `n ${maxN}`;
    commands.push(nCommand);
    commandString += nCommand + ";";

    direction = direction === "right" ? "left" : "right";
  });

  return {
    fileContent: commands.join("\n"),
    commandString: commandString.slice(0, -1), // Remove the last semicolon
  };
};

const downloadPattern = (patternData, setCommandString) => {
  const blob = new Blob([patternData.fileContent], { type: "text/plain" });
  const url = URL.createObjectURL(blob);
  const link = document.createElement("a");
  link.href = url;
  link.download = "pattern.txt";
  link.click();
  URL.revokeObjectURL(url);
  setCommandString(patternData.commandString);
};

const CreatePattern = ({ handleOwnPatternClick }) => {
  const [grid, setGrid] = useState([]);
  const [cols, setCols] = useState(19);
  const [rows, setRows] = useState(20);
  const [commandString, setCommandString] = useState("");
  const [sending, setSending] = useState(false);
  const [lastSentPattern, setLastSentPattern] = useState("");
  const [windowSize, setWindowSize] = useState({
    width: window.innerWidth,
    height: window.innerHeight,
  });

  useEffect(() => {
    const initialGrid = Array.from({ length: rows }, () => Array(cols).fill(0));
    setGrid(initialGrid);
  }, [rows, cols]);

  useEffect(() => {
    const handleResize = () => {
      setWindowSize({
        width: window.innerWidth,
        height: window.innerHeight,
      });
    };

    window.addEventListener("resize", handleResize);
    return () => window.removeEventListener("resize", handleResize);
  }, []);

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

  const calculateGridCellSize = () => {
    const containerWidth = Math.min(windowSize.width * 0.7, 400);
    const cellSize = Math.min(containerWidth / cols);
    return `${Math.floor(cellSize)}px`;
  };

  const toggleCellState = (rowIndex, colIndex) => {
    const updatedGrid = grid.map((row, i) =>
      i === rowIndex
        ? row.map((cell, j) => (j === colIndex ? (cell === 0 ? 1 : 0) : cell))
        : row
    );
    setGrid(updatedGrid);
    generateAndStorePattern(updatedGrid);
  };

  const generateAndStorePattern = (grid) => {
    const patternData = convertGridToPattern(grid);
    handleOwnPatternClick(patternData.commandString);
    setCommandString(patternData.commandString);
  };

  const handleDownload = () => {
    const patternData = convertGridToPattern(grid);
    downloadPattern(patternData, setCommandString);
  };

  const handleRowChange = (e) => {
    const newRows = parseInt(e.target.value, 10);
    setRows(newRows);
  };

  return (
    <div style={{ textAlign: "center" }}>
      <Content title="Create Your Pattern">
        <div className="max-w-4xl mx-auto bg-white p-12 rounded-2xl shadow-2xl">
          <p className="text-gray-700 mb-6 leading-relaxed text-lg">
            With our easy-to-use grid interface, you can quickly design your own
            knitting patterns. Each cell in the grid represents a stitch,
            allowing you to create detailed motifs and repeats. Blue cells
            represent skipped needles, giving you control over where the
            knitting machine will not make a stitch.
          </p>
          <div className="row-selector">
            <label htmlFor="rowCount">Rows: </label>
            <input
              type="number"
              id="rowCount"
              value={rows}
              onChange={handleRowChange}
              min={1}
              max={100}
              style={{ marginLeft: "10px" }}
            />
          </div>
        </div>
      </Content>

      <div
        className="grid-container"
        style={{
          display: "grid",
          justifyContent: "center",
          gridTemplateColumns: `repeat(${cols}, 1fr)`,
          gridTemplateRows: `repeat(${rows}, 1fr)`,
          margin: "0 auto",
          maxWidth: "400px",
        }}
      >
        {grid.map((row, rowIndex) =>
          row.map((cell, colIndex) => (
            <div
              key={`${rowIndex}-${colIndex}`}
              onClick={() => toggleCellState(rowIndex, colIndex)}
              className={`grid-cell ${cell === 1 ? "ticked" : ""}`}
              style={{
                width: calculateGridCellSize(),
                height: calculateGridCellSize(),
              }}
            ></div>
          ))
        )}
      </div>

      <div className="pattern-controls" style={{ marginTop: "20px" }}>
        <div
          style={{
            display: "flex",
            gap: "10px",
            justifyContent: "center",
            marginBottom: "20px",
          }}
        >
          <button onClick={handleDownload} className="download-btn">
            Download Pattern
          </button>

          <button
            onClick={() => sendToWemos(commandString)}
            className="download-btn"
            disabled={sending}
            style={{
              backgroundColor: sending ? "#ccc" : "#4a90e2",
              cursor: sending ? "not-allowed" : "pointer",
            }}
          >
            {sending ? "Sending..." : "Send to Device"}
          </button>
        </div>

        <div
          className="command-string-container"
          style={{
            maxWidth: "90%",
            margin: "20px auto",
            padding: "15px",
            backgroundColor: "#f5f5f5",
            borderRadius: "8px",
            overflowX: "auto",
          }}
        >
          <pre
            style={{
              whiteSpace: "pre-wrap",
              wordBreak: "break-word",
              margin: 0,
              textAlign: "left",
              fontFamily: "monospace",
            }}
          >
            {commandString}
          </pre>
        </div>
      </div>
    </div>
  );
};

export default CreatePattern;