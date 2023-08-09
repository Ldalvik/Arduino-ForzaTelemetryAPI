#include <ESP8266WiFi.h>
#include <ForzaTelemetryAPI.h>

const char *SSID = "YOUR_WIFI";
const char *PASSWORD = "YOUR_PASSWORD";

ForzaAPI forza = ForzaAPI();

void setup() {
  Serial.begin(115200);

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

  forza.connect();
  while (!forza.isConnected()) {
    delay(1000);
    Serial.println(".");
  }

  Serial.println("Data stream received.");
}

void onDataReceived(RawTelemetry telemetry) {
  // Open serial plotter to see real-time graphing
  Serial.print("Horsepower:");
  Serial.print(forza.getPower_Horsepower());
  Serial.print(",");
  Serial.print("Torque:");
  Serial.print(telemetry.Torque);
  Serial.print(",");
  // Static variables to keep the graph from resizing
  Serial.print("MaxHorsepower:");
  Serial.println(1250);
  Serial.print(",");
  Serial.print("TorqueDip:");
  Serial.println(-100);
}

void onCarChanged(RawTelemetry telemetry, Car car) {}
void onGamePaused(RawTelemetry telemetry) {}
void onGameUnpaused(RawTelemetry telemetry) {}

void loop() {
  forza.receive(onDataReceived, onCarChanged, onGamePaused, onGameUnpaused);
}