#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_SSID"; // replace with your SSID
const char* pass = "****"; // replace with your network pwd

const char* serverURL = "https://SERVER-URL/EP";
unsigned long previousMillis = 0;
const long interval = 2000; // Interval in milliseconds

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Make HTTP request
    HTTPClient http;
    http.begin(serverURL);
    int httpResponseCode = http.GET(); // Make the GET request

    if (httpResponseCode > 0) {
      String payload = http.getString(); // Get the response payload
      Serial.println("Response:");
      Serial.println(payload); // Print the response payload
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode); // Print error code
    }

    http.end(); // Free resources
  }
}
