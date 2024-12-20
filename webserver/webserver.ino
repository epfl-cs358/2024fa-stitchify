#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

const char* ssid = "Your_ssid";
const char* password = "Your_Password";

#define RX_PIN 16  // GPIO16 (RX2)
#define TX_PIN 17  // GPIO17 (TX2)

AsyncWebServer server(80);

// Helper function to print file list
void listFiles() {
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  //Serial.println("\n=== SPIFFS Files ===");
  while (file) {
    //Serial.printf("- %s (size: %d bytes)\n", file.name(), file.size());
    file = root.openNextFile();
  }
  // Serial.println("===================\n");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Initialize SPIFFS with detailed logging
  if (!SPIFFS.begin(true)) {
    //Serial.println("ERROR: SPIFFS Mount Failed");
    return;
  }

  // Print SPIFFS info
  // Serial.printf("SPIFFS Total: %d bytes\n", SPIFFS.totalBytes());
  //Serial.printf("SPIFFS Used: %d bytes\n", SPIFFS.usedBytes());
  listFiles();

  // WiFi Connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    //Serial.println("Connecting to WiFi...");
  }
  //Serial.printf("Connected! IP address: %s\n", WiFi.localIP().toString().c_str());

  // CORS Headers
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  // Serve static files
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Explicit routes for React build files
  server.serveStatic("/static/", SPIFFS, "/static/");
  server.serveStatic("/asset-manifest.json", SPIFFS, "/asset-manifest.json");

  // Request logging middleware
  server.on("/*", HTTP_GET, [](AsyncWebServerRequest * request) {
    //Serial.printf("GET Request: %s\n", request->url().c_str());

    // Check if file exists in SPIFFS
    if (SPIFFS.exists(request->url().c_str())) {
      // Serial.printf("File exists: %s\n", request->url().c_str());
      request->send(SPIFFS, request->url().c_str());
    } else {
      // Serial.printf("File NOT found: %s\n", request->url().c_str());
      // For React routing, serve index.html for missing files
      if (!request->url().endsWith(".js") &&
          !request->url().endsWith(".css") &&
          !request->url().endsWith(".json")) {
        request->send(SPIFFS, "/index.html");
      } else {
        request->send(404);
      }
    }
  });

  // Your existing send endpoint
  server.on("/send", HTTP_POST,
  [](AsyncWebServerRequest * request) {},
  NULL,
  [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    char *json = new char[len + 1];
    memcpy(json, data, len);
    json[len] = '\0';

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      // Serial.println("JSON Parse Error");
      request->send(400, "text/plain", "Invalid JSON");
      delete[] json;
      return;
    }

    const char* pattern = doc["item"];
    if (pattern) {
      Serial2.write(pattern);
      request->send(200, "text/plain", "Pattern received");
    } else {
      //Serial.println("No pattern in request");
      request->send(400, "text/plain", "No pattern found");
    }
    delete[] json;
  }
           );

  server.begin();
  //Serial.println("HTTP server started");
}

void loop() {
  // Empty
}
