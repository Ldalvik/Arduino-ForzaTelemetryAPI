#define s32 int
#define u32 unsigned int
#define f32 float
#define u16 unsigned short
#define s8 char
#define u8 unsigned char

struct Engine
{
    f32 MaxRpm;
    f32 IdleRpm;
    f32 CurrentRpm;
};

// In the car's local space; X = right, Y = up, Z = forward
struct Acceleration
{
    f32 X;
    f32 Y;
    f32 Z;
};

// In the car's local space; X = right, Y = up, Z = forward
struct Velocity
{
    f32 X;
    f32 Y;
    f32 Z;
};

// In the car's local space; X = pitch, Y = yaw, Z = roll
struct AngularVelocity
{
    f32 X;
    f32 Y;
    f32 Z;
};

struct Rotation
{
    f32 Yaw;
    f32 Pitch;
    f32 Roll;
};

// Suspension travel normalized: 0.0f = max stretch; 1.0 = max compression
struct NormalizedSuspensionTravel
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

// Tire normalized slip ratio, = 0 means 100% grip and |ratio| > 1.0 means loss of grip.
struct TireSlipRatio
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

typedef struct _Telemetry
{
    s32 IsRaceOn;    // = 1 when race is on. = 0 when in menus/race stopped …
    u32 TimestampMS; // Can overflow to 0 eventually
    struct Engine Engine;
    struct Acceleration Acceleration;
    struct Velocity Velocity;
    struct AngularVelocity AngularVelocity;
    struct Rotation Rotation;
    struct NormalizedSuspensionTravel NormalizedSuspensionTravel;
    struct TireSlipRatio TireSlipRatio;
    f32 WheelRotationSpeedFrontLeft; // Wheel rotation speed radians/sec.
    f32 WheelRotationSpeedFrontRight;
    f32 WheelRotationSpeedRearLeft;
    f32 WheelRotationSpeedRearRight;
    f32 WheelOnRumbleStripFrontLeft; // = 1 when wheel is on rumble strip, = 0 when off.
    f32 WheelOnRumbleStripFrontRight;
    f32 WheelOnRumbleStripRearLeft;
    f32 WheelOnRumbleStripRearRight;
    f32 WheelInPuddleDepthFrontLeft; // = from 0 to 1, where 1 is the deepest puddle
    f32 WheelInPuddleDepthFrontRight;
    f32 WheelInPuddleDepthRearLeft;
    f32 WheelInPuddleDepthRearRight;
    f32 SurfaceRumbleFrontLeft; // Non-dimensional surface rumble values passed to controller force feedback
    f32 SurfaceRumbleFrontRight;
    f32 SurfaceRumbleRearLeft;
    f32 SurfaceRumbleRearRight;
    f32 TireSlipAngleFrontLeft; // Tire normalized slip angle, = 0 means 100% grip and |angle| > 1.0 means loss of grip.
    f32 TireSlipAngleFrontRight;
    f32 TireSlipAngleRearLeft;
    f32 TireSlipAngleRearRight;
    f32 TireCombinedSlipFrontLeft; // Tire normalized combined slip, = 0 means 100% grip and |slip| > 1.0 means loss of grip.
    f32 TireCombinedSlipFrontRight;
    f32 TireCombinedSlipRearLeft;
    f32 TireCombinedSlipRearRight;
    f32 SuspensionTravelMetersFrontLeft; // Actual suspension travel in meters
    f32 SuspensionTravelMetersFrontRight;
    f32 SuspensionTravelMetersRearLeft;
    f32 SuspensionTravelMetersRearRight;
    s32 CarOrdinal;          // Unique ID of the car make/model
    s32 CarClass;            // Between 0 (D - lowest) and 7 (X class - highest) inclusive
    s32 CarPerformanceIndex; // Between 100 (lowest) and 999 (highest) inclusive
    s32 DrivetrainType;      // 0 = FWD, 1 = RWD, 2 = AWD
    s32 NumCylinders;        // Number of cylinders in the engine
    s32 CarType;             // Unique ID of the car make/model
    s8 obj1;
    s8 obj2;
    s8 obj3;
    s8 obj4;
    s8 obj5;
    s8 obj6;
    f32 PositionX;
    f32 PositionY;
    f32 PositionZ;
    f32 Speed;  // meters per second
    f32 Power;  // watts
    f32 Torque; // newton meter
    f32 TireTempFrontLeft;
    f32 TireTempFrontRight;
    f32 TireTempRearLeft;
    f32 TireTempRearRight;
    f32 Boost;
    f32 Fuel;
    f32 DistanceTraveled;
    f32 BestLap;
    f32 LastLap;
    f32 CurrentLap;
    f32 CurrentRaceTime;
    u16 LapNumber;
    u8 RacePosition;
    u8 Accel;
    u8 Brake;
    u8 Clutch;
    u8 HandBrake;
    u8 Gear;
    s8 Steer;
    s8 NormalizedDrivingLine;
    s8 NormalizedAIBrakeDifference;
    u8 padding;
} Telemetry;