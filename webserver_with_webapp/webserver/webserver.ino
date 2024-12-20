#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_Password";

AsyncWebServer server(80);

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  // Enable CORS
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  // Handle OPTIONS requests for CORS
  server.onNotFound([](AsyncWebServerRequest *request){
    if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->send(404);
    }
  });

  // Handle POST request to /send
  server.on("/send", HTTP_POST, 
    [](AsyncWebServerRequest *request){},
    NULL,
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      // Create a null-terminated string from request data
      char *json = new char[len + 1];
      memcpy(json, data, len);
      json[len] = '\0';

      // Parse JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, json);

      if (error) {
        Serial.println("JSON parsing failed");
        request->send(400, "text/plain", "Invalid JSON");
        delete[] json;
        return;
      }

      // Get the pattern string
      const char* pattern = doc["item"];
      if (pattern) {
        // Print the received pattern to the Serial Monitor
        //Serial.print("Received pattern: ");
        //Serial.println(pattern);
        Serial.write(pattern);

        request->send(200, "text/plain", "Pattern received");
      } else {
        request->send(400, "text/plain", "No pattern found in request");
      }

      delete[] json;
    }
  );

  // Serve files from SPIFFS
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Start the server
  server.begin();
}

void loop() {
  // No code needed here
}
