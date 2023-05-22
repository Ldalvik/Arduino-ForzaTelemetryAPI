#ifndef ForzaTelemetryAPI_h
#define ForzaTelemetryAPI_h
#include <WiFiUdp.h>
#include "math.h"
#include "forza.h"

class ForzaAPI
{
public:
    const int PACKET_SIZE = 324;
    Telemetry *telemetryData;

    typedef void (*OnDataReceived)();
    typedef void (*OnCarChanged)  ();
    typedef void (*OnGamePaused)  ();
    typedef void (*OnGameUnpaused)();

    ForzaAPI(const int port);
    void connect();
    bool isConnected();
    bool parse();
    void receive(OnDataReceived onDataReceived, OnCarChanged onCarChanged,
                 OnGamePaused onGamePaused, OnGameUnpaused onGameUnpaused);

    char * getCar_Class();
    char * getCar_DrivetrainType();
    char * getCar_Type();

    int getTireSlipAngle_FrontLeft():
    int getTireSlipAngle_FrontRight():
    int getTireSlipAngle_RearLeft():
    int getTireSlipAngle_RearRight():

    int getSpeed_KPH();
    int getSpeed_MPH();

    int getPower_Horsepower();
    
    int getAccel();
    int getBrake();
    int getClutch();
    int getHandbrake();
    int getGear();
    int getSteer();

    int getNormalizedDrivingLine();
    int getNormalizedAIBrakeDifference();
    
private:
    // Class variables
    int port;                  // Assigned UDP port. default 5300
    bool isPaused = false;     // Track last game state
    short lastOrdinal = false; // Track last car ordinal
    WiFiUDP UDP;               // UDP connection class
};

#endif