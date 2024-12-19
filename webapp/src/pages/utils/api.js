export const sendLineToWemos = async (line, setStatus) => {
  try {
    const response = await fetch("http://192.168.1.100/send", {
      // Replace with Wemos device IP
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ item: line }),
    });

    if (response.ok) {
      const result = await response.json();
      console.log(result);
      setStatus(`Data sent: ${line}`);
    } else {
      setStatus("Failed to send data");
    }
  } catch (error) {
    console.error("Error:", error);
    setStatus("Failed to send data");
  }
};

export const sendFileLines = (fileContent, setStatus) => {
  const lines = fileContent.split("\n");

  // Function to send each line with a delay
  const sendLineWithDelay = (index) => {
    if (index < lines.length) {
      sendLineToWemos(lines[index], setStatus);
      setTimeout(() => sendLineWithDelay(index + 1), 1000); // 1-second delay between sending lines
    } else {
      setStatus("All lines sent!");
    }
  };

  sendLineWithDelay(0); // Start with the first line
};
