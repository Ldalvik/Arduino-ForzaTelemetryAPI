#ifndef ForzaTelemetryAPI_h
#define ForzaTelemetryAPI_h
#include <WiFiUdp.h>
#include "math.h"
#include "forza.h"

class ForzaAPI
{
public:
    const int PACKET_SIZE = 324;

    typedef void (*OnDataReceived)(Telemetry *telemetryData);
    typedef void (*OnCarChanged)(Car car, short ordinal);
    typedef void (*OnGamePaused)(Telemetry *telemetryData);
    typedef void (*OnGameUnpaused)(Telemetry *telemetryData);

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

    float getSpeed_MetersPerSecond();
    float getSpeed_MilesPerHour();
    float getSpeed_KilometersPerHour();

    float getPower_Watts();
    float getPower_Horsepower();

    // float getBoost();
    // float getFuel();

    // int getRaceDistanceTraveled();
    // int getRaceBestLap();
    // int getRaceLastLap();
    // int getRaceCurrentLap();
    // int getRaceCurrentTime();
    // int getRaceLapNumber();
    // int getRacePosition();

    // int getAccel();
    // int getBrake();
    // int getClutch();
    // int getHandBrake();
    // int getGear();
    // int getSteer();

    // int getNormalizedDrivingLine();
    // int getNormalizedAIBrakeDifference();

private:
    int port;                  // Assigned UDP port. default 5300
    bool isPaused = false;     // Track last game state
    short lastOrdinal = 0; // Track last car ordinal
    WiFiUDP UDP;               // UDP connection class
    Telemetry *telemetryData;  // Telemetry data schema
};

#endif