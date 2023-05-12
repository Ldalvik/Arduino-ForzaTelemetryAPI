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

    char * getCarClass();
    char * getCarDrivetrainType();
    char * getCarType();

    // // ObjectHit is 2 ints or 1 long?
    // // unsigned char getObjectHit_1();
    // // unsigned char getObjectHit_2();
    // // unsigned char getObjectHit_3();
    // // unsigned char getObjectHit_4();
    // // unsigned char getObjectHit_5();
    // // unsigned char getObjectHit_6();
    // // unsigned char getObjectHit_7();
    // // unsigned char getObjectHit_8();

    // int getPositionX();
    // int getPositionY();
    // int getPositionZ();
    
    // int getSpeed_MetersPerSecond();
    // int getSpeed_MilesPerHour();
    // int getSpeed_KilometersPerHour();

    // int getPower_Watts();
    // int getPower_Horsepower();
    // int getTorque();
    
    // float getTireTempFrontLeft();
    // float getTireTempFrontRight();
    // float getTireTempMetersRearLeft();
    // float getTireTempRearRight();

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
    // Class variables
    int port;                  // Assigned UDP port. default 5300
    bool isPaused = false;     // Track last game state
    short lastOrdinal = false; // Track last car ordinal
    WiFiUDP UDP;               // UDP connection class
};

#endif