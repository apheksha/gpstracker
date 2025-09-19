# Location Tracker 

This project sends live GPS coordinates to ThingSpeak when the SOS button is pressed using:

- NEO-6M GPS Module
- ESP8266 (ESP-12E or NodeMCU)
- ThingSpeak cloud
- Emergency button (D5)

## Features
- Sends latitude and longitude on button press
- Data is logged to ThingSpeak
- Uses SoftwareSerial for GPS input
- HTTPClient to upload location

## Wiring
- GPS TX → D2
- GPS RX → D3
- Button between D5 and GND

## ThingSpeak Setup
- Create a channel with 2 fields (Latitude, Longitude)
- Replace your API key in the code
