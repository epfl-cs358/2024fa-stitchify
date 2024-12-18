import React, { useEffect } from "react";

const PatternDownload = ({ pattern }) => {
  useEffect(() => {
    if (pattern) {
      downloadPattern(pattern);
    }
  }, [pattern]);

  const sendToWemos = async (content) => {
    try {
      const lines = content.split("\n");
      for (const line of lines) {
        const response = await fetch("http://192.168.1.100/send", {
          // Replace with your Wemos IP
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ item: line }),
        });

        if (!response.ok) {
          throw new Error(`Failed to send data to Wemos for line: ${line}`);
        }
      }
    } catch (error) {
      console.error("Error sending to Wemos:", error);
      alert(`Unable to send the data to Wemos. Please try again.`);
    }
  };

  const downloadPattern = async (patternName) => {
    try {
      const fileMap = {
        "Pattern 1": "pattern1.txt",
        "Pattern 2": "pattern2.txt",
        "Pattern 3": "pattern3.txt",
      };

      const fileName = fileMap[patternName];

      if (!fileName) {
        throw new Error(`No file found for ${patternName}`);
      }

      const response = await fetch(`/${fileName}`);

      if (!response.ok) {
        throw new Error(`Failed to fetch ${fileName}`);
      }

      const content = await response.text();

      await sendToWemos(content);

      const file = new Blob([content], { type: "text/plain" });

      const link = document.createElement("a");
      link.href = URL.createObjectURL(file);
      link.download = fileName;

      document.body.appendChild(link);
      link.click();
      document.body.removeChild(link);

      URL.revokeObjectURL(link.href);
    } catch (error) {
      console.error("Download error:", error);
      alert(`Unable to download ${pattern}. Please try again.`);
    }
  };

  return null;
};

export default PatternDownload;
