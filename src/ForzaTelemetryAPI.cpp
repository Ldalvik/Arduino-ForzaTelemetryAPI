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

    if (getCarOrdinal() != lastOrdinal && !isPaused)
    {
      onCarChanged();
      lastOrdinal = getCarOrdinal();
    }

    if (!isPaused) // Remove this line if you want data to be received when the game is paused
      onDataReceived();
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

int ForzaAPI::getEngineMaxRpm()
{
  return round(telemetryData->Engine.MaxRpm);
}

int ForzaAPI::getEngineIdleRpm()
{
  return round(telemetryData->Engine.IdleRpm);
}

int ForzaAPI::getEngineCurrentRpm()
{
  return round(telemetryData->Engine.CurrentRpm);
}

int ForzaAPI::getAccelerationX()
{
  return round(telemetryData->Acceleration.X * 100);
}

int ForzaAPI::getAccelerationY()
{
  return round(telemetryData->Acceleration.Y * 100);
}

int ForzaAPI::getAccelerationZ()
{
  return round(telemetryData->Acceleration.Z * 100);
}

int ForzaAPI::getVelocityX()
{
  return round(telemetryData->Velocity.X * 100);
}

int ForzaAPI::getVelocityY()
{
  return round(telemetryData->Velocity.Y * 100);
}

int ForzaAPI::getVelocityZ()
{
  return round(telemetryData->Velocity.Z * 100);
}

int ForzaAPI::getAngularVelocityX()
{
  return round(telemetryData->AngularVelocity.X * 100);
}

int ForzaAPI::getAngularVelocityY()
{
  return round(telemetryData->AngularVelocity.Y * 100);
}

int ForzaAPI::getAngularVelocityZ()
{
  return round(telemetryData->AngularVelocity.Z * 100);
}

int ForzaAPI::getRotationYaw()
{
  return round(telemetryData->Rotation.Yaw * 100);
}

int ForzaAPI::getRotationPitch()
{
  return round(telemetryData->Rotation.Pitch * 100);
}

int ForzaAPI::getRotationRoll()
{
  return round(telemetryData->Rotation.Roll * 100);
}

// float getNormalizedSuspensionTravelFrontLeft();
// float getNormalizedSuspensionTravelFrontRight();
// float getNormalizedSuspensionTravelRearLeft();
// float getNormalizedSuspensionTravelRearRight();

// float getTireSlipRatioFrontLeft();
// float getTireSlipRatioFrontRight();
// float getTireSlipRatioRearLeft();
// float getTireSlipRatioRearRight();

// int getWheelRotationSpeedFrontLeft();
// int getWheelRotationSpeedFrontRight();
// int getWheelRotationSpeedRearLeft();
// int getWheelRotationSpeedRearRight();

// float getWheelOnRumbleStripFrontLeft();
// float getWheelOnRumbleStripFrontRight();
// float getWheelOnRumbleStripRearLeft();
// float getWheelOnRumbleStripRearRight();

// float getWheelInPuddleDepthFrontLeft();
// float getWheelInPuddleDepthFrontRight();
// float getWheelInPuddleDepthRearLeft();
// float getWheelInPuddleDepthRearRight();

// float getSurfaceRumbleFrontLeft();
// float getSurfaceRumbleFrontRight();
// float getSurfaceRumbleRearLeft();
// float getSurfaceRumbleRearRight();

// float getTireSlipAngleFrontLeft();
// float getTireSlipAngleFrontRight();
// float getTireSlipAngleRearLeft();
// float getTireSlipAngleRearRight();

// float getTireCombinedSlipFrontLeft();
// float getTireCombinedSlipFrontRight();
// float getTireCombinedSlipRearLeft();
// float getTireCombinedSlipRearRight();

// float getSuspensionTravelMetersFrontLeft();
// float getSuspensionTravelMetersFrontRight();
// float getSuspensionTravelMetersRearLeft();
// float getSuspensionTravelMetersRearRight();

int ForzaAPI::getCarOrdinal()
{
  return telemetryData->Car.Ordinal;
}
// int getCarClass();
// int getCarPerformanceIndex();
// int getCarDrivetrainType();
// int getNumCylinders();
// int getCarType();

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
