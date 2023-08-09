#include "ForzaTelemetryAPI.h"

ForzaAPI::ForzaAPI(const int port)
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
      memcpy(&telemetryData, packetData, sizeof(Telemetry));
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
    if (!telemetryData.IsRaceOn && !isPaused)
    {
      onGamePaused(telemetryData);
      isPaused = true;
    }
    else if (telemetryData.IsRaceOn && isPaused)
    {
      onGameUnpaused(telemetryData);
      isPaused = false;
    }

    if (telemetryData.Car.Ordinal != lastOrdinal && !isPaused)
    {
      onCarChanged(telemetryData.Car);
      lastOrdinal = telemetryData.Car.Ordinal;
    }

    if (!isPaused) // Remove this line if you want data to be received when the game is paused
      onDataReceived(telemetryData);
  }
}

int ForzaAPI::getTireSlipAngle_FrontLeft()
{
  return telemetryData.TireSlipAngle.FrontLeft * 180 / M_PI;
}

int ForzaAPI::getTireSlipAngle_FrontRight()
{
  return telemetryData.TireSlipAngle.FrontRight * 180 / M_PI;
}

int ForzaAPI::getTireSlipAngle_RearLeft()
{
  return telemetryData.TireSlipAngle.RearLeft * 180 / M_PI;
}

int ForzaAPI::getTireSlipAngle_RearRight()
{
  return telemetryData.TireSlipAngle.RearRight * 180 / M_PI;
}

String ForzaAPI::getCarClass()
{
  switch (telemetryData.Car.Class)
  {
  case 0:
    return "D";
    break;
  case 1:
    return "C";
    break;
  case 2:
    return "B";
    break;
  case 3:
    return "A";
    break;
  case 4:
    return "S1";
    break;
  case 5:
    return "S2";
    break;
  case 6:
    return "X";
    break;
  default:
    return "-";
    break;
  }
}

String ForzaAPI::getCarDrivetrainType()
{
  switch (telemetryData.Car.DrivetrainType)
  {
  case 0:
    return "FWD";
    break;
  case 1:
    return "RWD";
    break;
  case 2:
    return "AWD";
    break;
  default:
    return "-";
    break;
  }
}

String ForzaAPI::getCarType()
{
  switch (telemetryData.Car.Type)
  {
  case 11:
    return "Modern Super Cars";
    break;
  case 12:
    return "Retro Super Cars";
    break;
  case 13:
    return "Hyper Cars";
    break;
  case 14:
    return "Retro Saloons";
    break;
  case 16:
    return "Vans & Utility";
    break;
  case 17:
    return "Retro Sports Cars";
    break;
  case 18:
    return "Modern Sports Cars";
    break;
  case 19:
    return "Super Saloons";
    break;
  case 20:
    return "Classic Racers";
    break;
  case 21:
    return "Cult Cars";
    break;
  case 22:
    return "Rare Classics";
    break;
  case 25:
    return "Super Hot Hatch";
    break;
  case 29:
    return "Rods & Customs";
    break;
  case 30:
    return "Retro Muscle";
    break;
  case 31:
    return "Modern Muscle";
    break;
  case 32:
    return "Retro Rally";
    break;
  case 33:
    return "Classic Rally";
    break;
  case 34:
    return "Rally Monsters";
    break;
  case 35:
    return "Modern Rally";
    break;
  case 36:
    return "GT Cars";
    break;
  case 37:
    return "Super GT";
    break;
  case 38:
    return "Extreme Offroad";
    break;
  case 39:
    return "Sports Utility Heroes";
    break;
  case 40:
    return "Offroad";
    break;
  case 41:
    return "Offroad Buggies";
    break;
  case 42:
    return "Classic Sports Cars";
    break;
  case 43:
    return "Track Toys";
    break;
  case 44:
    return "Vintage Racers";
    break;
  case 45:
    return "Trucks";
    break;
  default:
    return "-";
    break;
  }
}

float ForzaAPI::getSpeed_MetersPerSecond()
{
  return telemetryData.Speed;
}

float ForzaAPI::getSpeed_MilesPerHour()
{
  return telemetryData.Speed * 2.23694;
}

float ForzaAPI::getSpeed_KilometersPerHour()
{
  return telemetryData.Speed * 3.6;
}

float ForzaAPI::getPower_Watts()
{
  return telemetryData.Torque;
}

float ForzaAPI::getPower_Horsepower()
{
  return telemetryData.Power * 0.00134102;
}
