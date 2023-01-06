#include "ForzaTelemetryAPI.h"

ForzaAPI::ForzaAPI(const int port = 5300)
{
  this->port = port;
}

void ForzaAPI::connect()
{
  UDP.begin(port);
}

bool ForzaAPI::isConnected()
{
  return UDP.parsePacket() == PACKET_SIZE;
}

bool ForzaAPI::parse()
{
  char packetData[PACKET_SIZE];
  if (UDP.parsePacket() == PACKET_SIZE)
  {
    int length = UDP.read(packetData, PACKET_SIZE);
    if (length > 0)
    {
      telemetryData = (Telemetry*) packetData;
      return true;
    } else return false;
  } else return false;
}

void ForzaAPI::receive(OnDataReceived onDataReceived, OnCarChanged onCarChanged,
                 OnGamePaused onGamePaused, OnGameUnpaused onGameUnpaused)
{
  if (parse())
  {
    if (!getIsRaceOn() && !isPaused)
    {
      onGamePaused();
      isPaused = true;
    }
    else if (getIsRaceOn() && isPaused)
    {
      onGameUnpaused();
      isPaused = false;
    }

    if(getCarOrdinal() != lastOrdinal && !isPaused)
    {
      onCarChanged();
      lastOrdinal = getCarOrdinal();
    }

    if (!isPaused) onDataReceived();
  }
}

int ForzaAPI::getIsRaceOn()
{
  return telemetryData->IsRaceOn;
}

long ForzaAPI::getTimestampMS()
{
  return telemetryData->TimestampMS;
}

float ForzaAPI::getEngineMaxRPM()
{
  return round(telemetryData->EngineMaxRpm);
}

float ForzaAPI::getEngineIdleRPM()
{
  return round(telemetryData->EngineIdleRpm);
}

float ForzaAPI::getCurrentEngineRPM()
{
  return round(telemetryData->CurrentEngineRpm);
}
