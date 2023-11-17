#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include "ForzaTelemetryAPI.h"

const char *SSID = "YOUR_WIFI";
const char *PASSWORD = "YOUR_PASSWORD";

ForzaAPI forza = ForzaAPI();

void setup()
{
  Serial.begin(115200);

  // This is the device IP for your ESP board - make sure you use the same address in-game.
  Serial.print("Connecting to ");
  Serial.println(String(SSID));

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Searching for data stream...");

  forza.connect(); // Begin UDP connection
  while (!forza.isConnected())
  { // Wait for the first stream of data to come in
    delay(1000);
    Serial.println(".");
  }

  Serial.println("Data stream received.");
}

/*
 * OnDataReceived - this will be called whenever data is received. This is usually
 * once every 33.33ms, or 30 frames per second. Data will not be received here if the game is paused.
 * If you'd like data to be received here even when paused, uncomment line 56 in ForzaTelemetry.cpp
 */
void onDataReceived(RawTelemetry telemetry)
{
  // Access data directly from the data packet
  Serial.print("Speed (meters/s): ");
  Serial.print(telemetry.Speed);
  Serial.print("    -    ");

  // Access data via API helper functions
  Serial.print("Speed (mph): ");
  Serial.print(forza.getSpeed_MilesPerHour());
  Serial.print("    -    ");
  Serial.print("Speed (kph): ");
  Serial.print(forza.getSpeed_KilometersPerHour());

  // Access structured data from the API
  Serial.print("Current RPM: ");
  Serial.print(forza.telemetryData.Engine.CurrentRpm);
  Serial.print(", Idle RPM: ");
  Serial.print(forza.telemetryData.Engine.IdleRpm);
  Serial.print(", Max RPM: ");
  Serial.println(forza.telemetryData.Engine.MaxRpm);
}

/*
 * OnCarChanged - this will be called ONCE when the player switches cars (tracked by car ordinal).
 * All relevant data is under the "Car" struct, onDataReceived will run in the same frame as 
 * onCarChanged, so that frame won't be skipped.
 */
void onCarChanged(Car car)
{
  Serial.println("---- New car ---- ");
  Serial.print("Ordinal: ");
  Serial.println(car.Ordinal);

  // Get text version of car class
  Serial.print("Class: ");
  Serial.println(forza.getCarClass());
  // Serial.print("Class: "); Serial.println(car.Class);

  // Get text version of drivetrain type
  Serial.print("Drivetrain type: ");
  Serial.println(forza.getCarDrivetrainType());
  // Serial.print("Drivetrain type: "); Serial.println(car.DrivetrainType);

  Serial.print("# of cyclinders: ");
  Serial.println(car.NumCylinders);

  // Get text version of car type
  Serial.print("Type: ");
  Serial.println(forza.getCarType());
  // Serial.print("Type: "); Serial.println(car.Type);

  Serial.print("Performance Index (PI): ");
  Serial.println(car.PerformanceIndex);
}

/*
 * OnGamePaused - this will be called ONCE when the player pauses the game.
 * Remember that no other data will be received while the game is paused. If you'd like to continue receiving
 * updates to OnDataReceived while the game is paused, remove line 58 from 'ForzaTelemetryAPI.cpp'.
 * Please note that the only data that is updated while the game is paused is the Timestamp.
 */
void onGamePaused(RawTelemetry telemetry)
{
  Serial.print("Game paused at ");
  Serial.println(telemetry.TimestampMS);
}

/*
 * OnGameUnpaused - this will be called ONCE when the player unpauses the game. Data will begin to be
 * received in OnDataReceived.
 */
void onGameUnpaused(RawTelemetry telemetry)
{
  Serial.print("Game unpaused at ");
  Serial.println(telemetry.TimestampMS);
}

// Update event listeners
void loop()
{
  forza.receive(onDataReceived, onCarChanged, onGamePaused, onGameUnpaused);
}