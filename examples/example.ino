#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
#include <ForzaTelemetryAPI.h>

const char* SSID = "WiFi_SSID";
const char* PASSWORD = "WiFi_Password";

int UDP_PORT = 5300 // Port to read data from - make sure you use the same port in-game.

ForzaAPI forza(UDP_PORT);

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID, PASSWORD); // Connect to WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  // This is the device IP for your ESP board - make sure you use the same address in-game.
  Serial.print("Connected! IP address (use this in-game): ");
  Serial.println(WiFi.localIP());

  Serial.println("Searching for data stream...");

  forza.connect();                // Begin UDP connection
  while (!forza.isConnected()) {} // Wait for the first stream of data to come in

  Serial.println("Data stream received.");
}

/* 
 * OnDataReceived - this will be called whenever data is received. This is usually
 * once every 33.33ms, or 30 frames per second. Data will not be received here if the game is paused.
 */
void onDataReceived() {
  Serial.println(forza.telemetryData->Engine.CurrentRpm);
}

/*
 * OnCarChanged - this will be called ONCE when the player switches cars (tracked by car ordinal).
 * All relevant data is under the "Car" struct, otherwise use the helper methods which may return more descriptive data.
 */
void onCarChanged() {
  Serial.print("New car Performance Index (Number): ");
  Serial.println(forza.telemetryData->Car.PerformanceIndex); // Returns number value of PI

  Serial.print("New car Performance Index (Class): ");
  Serial.println(forza.getCarPerformanceIndex()); // Returns text value of PI
}

/* 
 * OnGamePaused - this will be called ONCE when the player pauses the game.
 * Remember that no other data will be received while the game is paused. If you'd like to continue receiving 
 * updates to OnDataReceived while the game is paused, remove line 58 from 'ForzaTelemetryAPI.cpp'.
 * Please note that the only data that is updated while the game is paused is the Timestamp.
*/
void onGamePaused() {
  Serial.print("Game paused at ");
  Serial.println(forza.getTimestampMS());
}

/* 
 * OnGameUnpaused - this will be called ONCE when the player unpauses the game. Data will begin to be 
 * received in OnDataReceived.
 */
void onGameUnpaused() {
  Serial.print("Game unpaused at ");
  Serial.println(forza.getTimestampMS());
}

void loop() {
  // Set event listeners 
  forza.receive(onDataReceived, onCarChanged, onGamePaused, onGameUnpaused);
}
