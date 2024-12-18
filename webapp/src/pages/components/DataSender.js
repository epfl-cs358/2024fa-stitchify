import React, { useState, useEffect } from "react";
import { sendFileLines } from "../utils/api";

const DataSender = () => {
  const [status, setStatus] = useState("");

  const fetchFileContent = async () => {
    try {
      const response = await fetch("/file.txt");
      if (response.ok) {
        const fileContent = await response.text();
        sendFileLines(fileContent, setStatus);
      } else {
        setStatus("Failed to load file");
      }
    } catch (error) {
      setStatus("Error fetching the file");
      console.error(error);
    }
  };

  useEffect(() => {
    fetchFileContent();
  }, []);

  return (
    <div>
      <h1>Send File Line by Line to Wemos</h1>
      <p>Status: {status}</p>
    </div>
  );
};

export default DataSender;
