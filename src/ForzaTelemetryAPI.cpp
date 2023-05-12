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
      telemetryData = (Telemetry *)packetData;
      return true;
    }
    else
      return false;
  }
  else
    return false;
}

void ForzaAPI::receive(OnDataReceived onDataReceived, OnCarChanged onCarChanged,
                       OnGamePaused onGamePaused, OnGameUnpaused onGameUnpaused)
{
  if (parse())
  {
    if (!telemetryData->IsRaceOn && !isPaused)
    {
      onGamePaused();
      isPaused = true;
    }
    else if (telemetryData->IsRaceOn && isPaused)
    {
      onGameUnpaused();
      isPaused = false;
    }

    if (telemetryData->Car.Ordinal != lastOrdinal && !isPaused)
    {
      onCarChanged();
      lastOrdinal = telemetryData->Car.Ordinal;
    }

    if (!isPaused) // Remove this line if you want data to be received when the game is paused
      onDataReceived();
  }
}

// telemetryData->TireSlipAngle.FrontLeft * 180 / M_PI

char *ForzaAPI::getCarClass()
{
  switch (telemetryData->Car.Class)
  {
  case 0:
    return 'D' break;
  case 1:
    return 'C' break;
  case 2:
    return 'B' break;
  case 3:
    return 'A' break;
  case 4:
    return 'S1' break;
  case 5:
    return 'S2' break;
  case 6:
    return 'X' break;
  default:
    return '-' break;
  }
}

char * ForzaAPI::getCarDrivetrainType()
{
 switch (telemetryData->Car.DrivetrainType)
  {
  case 0:
    return 'FWD' break;
  case 1:
    return 'RWD' break;
  case 2:
    return 'AWD' break;
  default:
    return '-' break;
  }
}

char * ForzaAPI::getCarType()
{
  switch (telemetryData->Car.Type)
  {
  case 11:
    return "Modern Super Cars" break;
  case 12:
    return "Retro Super Cars" break;
  case 13:
    return "Hyper Cars" break;
  case 14:
    return "Retro Saloons" break;
  case 16:
    return "Vans & Utility" break;
  case 17:
    return "Retro Sports Cars" break;
 
  default:
    return '-' break;
  }
}
