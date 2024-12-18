#include <WiFi.h>
#include <WebServer.h>
#include <SoftwareSerial.h>

// Wi-Fi credentials
const char* ssid = "Your_SSId";
const char* password = "Your_PASSWORD";

// Web server on port 80
WebServer server(80);

// Define software serial pins
#define TX_PIN 17  // Choose an available GPIO pin
#define RX_PIN 16  // Choose an available GPIO pin (not used but required for SoftwareSerial)

// Initialize software serial
SoftwareSerial arduinoSerial(RX_PIN, TX_PIN); // RX, TX

// HTML page with a text input form
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Text Input</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 30px; }
        h1 { color: #444; }
        form { margin-top: 20px; }
        input[type="text"] {
            padding: 10px; width: 70%; font-size: 16px;
        }
        input[type="submit"] {
            padding: 10px 20px; font-size: 16px; cursor: pointer; color: #fff; background-color: #007BFF; border: none; border-radius: 5px;
        }
    </style>
</head>
<body>
    <h1>Send a Message</h1>
    <form action="/send" method="post">
        <input type="text" name="message" placeholder="Enter your message here">
        <input type="submit" value="Send">
    </form>
</body>
</html>
)rawliteral";

// Handler for root page
void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

// Handler for receiving and printing the message
void handleSend() {
    if (server.hasArg("message")) {
        String message = server.arg("message");
        
        // Print to Serial Monitor
        Serial.print("Received message: ");
        Serial.println(message);
        
        // Send to Arduino
        arduinoSerial.println(message);  // Send message with newline
        
        server.send(200, "text/html", htmlPage);
    } else {
        server.send(200, "text/html", htmlPage);
    }
}

void setup() {
    // Initialize hardware serial for debugging
    Serial.begin(115200);
    
    // Initialize software serial for Arduino communication
    arduinoSerial.begin(9600);  // Standard Arduino baud rate

    // Initialize Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Configure web server routes
    server.on("/", handleRoot);
    server.on("/send", HTTP_POST, handleSend);

    // Start server
    server.begin();
    Serial.println("HTTP server started.");
}

void loop() {
    server.handleClient();
}