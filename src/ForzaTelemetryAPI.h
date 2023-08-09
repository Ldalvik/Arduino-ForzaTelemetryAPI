#ifndef ForzaTelemetryAPI_h
#define ForzaTelemetryAPI_h
#include <WiFiUdp.h>
#include "math.h"
#include "forza.h"

class ForzaAPI
{
public:
    const int PACKET_SIZE = 324;
    Telemetry telemetryData; // Named telemetry data schema

    using OnDataReceived = std::function<void(RawTelemetry)>;
    using OnCarChanged = std::function<void(Car)>;
    using OnGamePaused = std::function<void(RawTelemetry)>;
    using OnGameUnpaused = std::function<void(RawTelemetry)>;

    ForzaAPI(const int port = 5300);
    void connect();
    bool isConnected();
    bool parse();
    void receive(OnDataReceived onDataReceived, OnCarChanged onCarChanged,
                 OnGamePaused onGamePaused, OnGameUnpaused onGameUnpaused);

    int getTireSlipAngle_FrontLeft();
    int getTireSlipAngle_FrontRight();
    int getTireSlipAngle_RearLeft();
    int getTireSlipAngle_RearRight();

    String getCarClass();
    String getCarDrivetrainType();
    String getCarType();

    float getSpeed_MilesPerHour();
    float getSpeed_KilometersPerHour();

    float getPower_Horsepower();

    float getSteeringAngle();

private:
    int port;                      // Assigned UDP port. default 5300
    bool isPaused = false;         // Track last game state
    short lastOrdinal = 0;         // Track last car ordinal
    WiFiUDP UDP;                   // UDP connection class
    RawTelemetry rawTelemetryData; // Raw telemetry data schema
};

#endif