#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "apheksha";
const char* password = "80193807";
String apiKey = "NT7I3BT689BAJAPU";
const char* server = "http://api.thingspeak.com/update";

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D2, D3); 

#define BUTTON_PIN D5

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    if (gps.location.isValid() && gps.location.isUpdated()) {
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();

      Serial.print("Button Pressed: Sending GPS to ThingSpeak...");
      Serial.print("Lat: "); Serial.print(latitude, 6);
      Serial.print(" | Lng: "); Serial.println(longitude, 6);

      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = String(server) + "?api_key=" + apiKey +
                     "&field1=" + String(latitude, 6) +
                     "&field2=" + String(longitude, 6);
        WiFiClient client;
http.begin(client, url);
        int httpCode = http.GET();
        http.end();

        Serial.print("HTTP Response Code: ");
        Serial.println(httpCode);
      } else {
        Serial.println("WiFi Disconnected!");
      }

      delay(5000);  
    } else {
      Serial.println("Waiting for valid GPS fix...");
    }
  }
}