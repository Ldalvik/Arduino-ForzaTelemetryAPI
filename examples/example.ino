#include <ESP8266WiFi.h>
#include <ForzaTelemetryAPI.h>

const char *SSID = "YOUR_WIFI";
const char *PASSWORD = "YOUR_PASSWORD";

ForzaAPI forza();

void setup() {
  Serial.begin(115200);

  // This is the device IP for your ESP board - make sure you use the same address in-game.
  Serial.print("Connecting to ");
  Serial.println(String(SSID));

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Searching for data stream...");

  forza.connect();                // Begin UDP connection
  while (!forza.isConnected()) {  // Wait for the first stream of data to come in
    delay(1000);
    Serial.println(".");
  }

  Serial.println("Data stream received.");
}

/* 
 * OnDataReceived - this will be called whenever data is received. This is usually
 * once every 33.33ms, or 30 frames per second. Data will not be received here if the game is paused.
 */
void onDataReceived(Telemetry *telemetry) {
  Serial.print("Speed (meters/s): ");
  Serial.println(telemetry->Speed);
  Serial.print("Speed (meters/s): ");
  Serial.println(telemetry->Speed);
}

/*
 * OnCarChanged - this will be called ONCE when the player switches cars (tracked by car ordinal).
 * All relevant data is under the "Car" struct, otherwise use the helper methods which may return more descriptive data.
 */
void onCarChanged(Car car, short ordinal) {
  Serial.println("---- New car ---- ");
  Serial.print("Ordinal: "); Serial.println(ordinal);
}

/* 
 * OnGamePaused - this will be called ONCE when the player pauses the game.
 * Remember that no other data will be received while the game is paused. If you'd like to continue receiving 
 * updates to OnDataReceived while the game is paused, remove line 58 from 'ForzaTelemetryAPI.cpp'.
 * Please note that the only data that is updated while the game is paused is the Timestamp.
*/
void onGamePaused(Telemetry *telemetry) {
  Serial.print("Game paused at ");
  Serial.println(telemetry->TimestampMS);
}

/* 
 * OnGameUnpaused - this will be called ONCE when the player unpauses the game. Data will begin to be 
 * received in OnDataReceived.
 */
void onGameUnpaused(Telemetry *telemetry) {
  Serial.print("Game unpaused at ");
  Serial.println(telemetry->TimestampMS);
}

// Update event listeners 
void loop() {
  forza.receive(onDataReceived, onCarChanged, onGamePaused, onGameUnpaused);
}