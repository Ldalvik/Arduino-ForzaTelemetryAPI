# Espressif-ForzaTelemetryAPI

This library was made to simplify the usage of FH5 telemetry data on Espressif hardware.

This can be used for many things, such as graphing tire slip angles or suspension compression to tune a car. Sim-rigs or "motion sleds" also use this type of connection to simulate whats happening in-game, like causing rumble.shaking or vibrations based on things like "WheelOnRumbleStrip" or "SurfaceRumble" values (imagine how your controller vibrates when driving on certain terrain).

## How to use - setup

Install the library by downloading this repository, and adding it to your ```/Arduino/libraries/``` folder. If you are using something like Platform.IO on VSCode, extract the files into your ```/lib``` equivalent directory.

Once you are sure the library is installed, import the header file and initialize the library at the top of your main file.

``` C
#include "ForzaTelemetryAPI.h"

ForzaAPI forza = ForzaAPI();
```

By default, the port is 5300. To use a different port, pass it to the constructor. Make sure you set DATA OUT PORT to the same value as well. You can find it at the very bottom of HUD AND GAMEPLAY

``` C
ForzaAPI forza = ForzaAPI(5200); // Using a different port
```

Since we are using UDP transfer protocol over WiFi, we have to connect to the network your game is running on. Add the ```WiFi.h``` library (or ```WiFi8266.h``` for ESP8266). Pass your network SSID and password to ```WiFi.begin()``` and wait for it to connect. If you've used an ESP chip before you should be familiar with this. 

Here is an example:

``` C
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

const char *SSID = "YOUR_WIFI";
const char *PASSWORD = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(String(SSID));

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected!");
}
```

If your credentials are correct, you should see "Connected!" in your terminal after a few seconds of waiting.

This next step is important. You need to print out your devices assigned IP after connecting to WiFi, and type that address into the DATA OUT IP ADDRESS in your Forza Horizon 5 settings. This can be found at the bottom of the HUD AND GAMEPLAY menu.

``` C
Serial.print("Device IP: ");
Serial.println(WiFi.localIP());
```

Now that you're connected to WiFi, and you printed out the devices IP, you can add the UDP connection code to begin receiving data. Add this below the previous code in the setup function:

``` C
  forza.connect();
  while (!forza.isConnected()) {
    delay(1000);
    Serial.println(".");
  }

  Serial.println("Data stream received.");
```

The ```connect()``` function begins the UDP connection, which will begin waiting for packets on the given port. ```isConnected()``` checks if the packet received is equal to the size of a telemetry packet, which is 324 bytes. If you're connected to the correct network (both chip and device running Forza), set the right port and IP address, and saved your changes, then you should see "Data stream received." almost immedietely.

That's it for the setup! If everthing went well, you're ready to start receiving data and do stuff with it. Here's the complete code so far if you need it:

``` C
// Makes sure we use the right header
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include "ForzaTelemetryAPI.h"

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
```

## How to use - receiving data

Now that you're ready to receive data, add the 4 listener functions to your sketch.
``` C
void onDataReceived(RawTelemetry telemetry) {

}

void onCarChanged(Car car) {

}

void onGamePaused(RawTelemetry telemetry) {

}

void onGameUnpaused(RawTelemetry telemetry) {

}
```

```onDataReceived```: This will be called whenever data is received. This is usually once every 33.33ms, or 30 frames per second. Data will not be received here if the game is paused. To continue receiving updates to OnDataReceived while the game is paused, remove line 53 from ```ForzaTelemetryAPI.cpp```. Note that the only data that is updated while the game is paused is the Timestamp.

```onCarChanged```: This will be called ONCE when the player switches cars (tracked by car ordinal). All relevant data is under the "Car" struct, onDataReceived will run in the same frame as onCarChanged, so that frame won't be skipped.

```onGamePaused```: This will be called ONCE when the player pauses the game. No other data will be received while the game is paused. To continue receiving updates to OnDataReceived while the game is paused, remove line 53 from ```ForzaTelemetryAPI.cpp```. Note that the only data that is updated while the game is paused is the Timestamp.

```onGameUnpaused```: This will be called ONCE when the player unpauses the game. Data will begin to be received in OnDataReceived.

To receive data in these listeners, you have to pass them to the ```receive()``` function. It has to check for new data constantly, so put it in your loop like this.

``` C
 void loop()
{
  forza.receive(onDataReceived, onCarChanged, onGamePaused, onGameUnpaused);
}
```

Now you can start to do stuff with the data! You can see all the available data points for ```Telemetry``` and ```RawTelemetry``` in the ```forza.h``` file. You can also use your IDEs autocomplete. Example code is available here: https://github.com/Ldalvik/Espressif-ForzaTelemetryAPI/tree/master/examples

# Documentation - Public functions/variables

### ```connect() [void]```
Begins UDP connection to the specified port

### ```isConnected() [boolean]```
Returns false until the data being received matches the telemetry packet size (324 bytes).

### ```receive(OnDataReceived, OnCarChanged, OnGamePaused, OnGameUnpaused) [void]```
Passes telemetry data to the functions in the parameters. All functions must have the ```RawTelemetry``` parameter, except for ```OnCarChanged``` which passes the ```Car``` struct.

Note: Parameter functions can be named anything, but the data received will stay in the same order: OnDataReceived, OnCarChanged, OnGamePaused, OnGameUnpaused. (The only strict typing this has is the second parameter [```OnCarChanged```] must have a ```Car``` parameter, so make sure you're passing the rest correctly)

### ```ForzaAPI.telemetryData [Telemetry]```
When data is actively being received, you can use this in any part of your sketch (it comes from the global class, similar to the helper functions below) to get structured data. The ```Telemetry``` struct has a more compact naming structure if you rather use this instead of ```RawTelemetry``` for whatever reason. To use it in your code, call it from your ForzaAPI class directly:

``` C
void onDataReceived(RawTelemetry telemetry) {
  // Access structured data from the API
  Serial.print("Current RPM: ");
  Serial.print(forza.telemetryData.Engine.CurrentRpm);
  Serial.print(", Idle RPM: ");
  Serial.print(forza.telemetryData.Engine.IdleRpm);
  Serial.print(", Max RPM: ");
  Serial.println(forza.telemetryData.Engine.MaxRpm);
}
```

# Documentation - Helper functions

### ```getTireSlipAngle_[Front/Rear][Left/Right]() [int]```
Returns the calculated slip angle as degrees instead of radians.

### ```getCarClass() [int]```
Returns the current performance class of your car. (D, C, B, A, S1, S2, X)

### ```getCarDrivetrainType() [int]```
Returns the current drivetrain installed on your car. (RWD, FWD, AWD)

### ```getCarType() [int]```
Returns the category of car. (Modern Rally, Rare Classics, Offroad, etc.)

### ```getSpeed_MilesPerHour() [float]```
Returns your cars current speed in miles per hour.

### ```getSpeed_KilometersPerHour() [float]```
Returns your cars current speed in kilometers per hour.

### ```getPower_Horsepower() [float]```
Returns your cars current power output in horsepower.

### ```getSteeringAngle() [float]```
Returns your cars current steering angle from -100 (turing left) to +100 (turning right)

