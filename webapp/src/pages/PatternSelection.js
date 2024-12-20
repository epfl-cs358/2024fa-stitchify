import React, { useState } from "react";

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
    console.log('Attempting to send pattern:', patternString);
    setSending(true);
    try {
      const apiUrl = `http://172.21.69.170/send`;
      console.log('Sending to URL:', apiUrl);
      
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
      console.log('Pattern sent successfully:', patternString);
    } catch (error) {
      console.error('Error sending pattern:', error);
    } finally {
      setSending(false);
    }
  };

  return (
    <div className="p-4">
      <h2 className="text-2xl font-bold mb-4">Select a Pattern to Send</h2>
      
      {lastSentPattern && (
        <div className="bg-green-100 border border-green-400 text-green-700 px-4 py-3 rounded mb-4">
          Last sent pattern: {lastSentPattern}
        </div>
      )}

      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
        {patterns.map((pattern) => (
          <div key={pattern.name} className="p-4 border rounded">
            <h3 className="text-xl font-bold mb-2">{pattern.name}</h3>
            <p className="mb-2">{pattern.description}</p>
            <button
              className="bg-blue-500 text-white px-4 py-2 rounded disabled:bg-gray-400"
              onClick={() => sendToWemos(pattern.patternString)}
              disabled={sending}
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
