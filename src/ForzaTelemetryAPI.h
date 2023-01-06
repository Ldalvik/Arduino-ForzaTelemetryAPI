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

    int getIsRaceOn();
    long getTimestampMS();

    float getEngineMaxRPM();
    float getEngineIdleRPM();
    float getCurrentEngineRPM();

private:
    // Class variables
    int port;                  // Assigned UDP port. default 5300
    bool isPaused = false;     // Track last game state
    short lastOrdinal = false; // Track last game state
    WiFiUDP UDP;               // UDP connection class
};

#endif