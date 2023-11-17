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

// Wheel rotation speed radians/sec.
struct WheelRotationSpeed
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

// = 1 when wheel is on rumble strip, = 0 when off.
struct WheelOnRumbleStrip
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

// = from 0 to 1, where 1 is the deepest puddle
struct WheelInPuddleDepth
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

struct SurfaceRumble
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

struct TireSlipAngle
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

struct TireCombinedSlip
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

struct SuspensionTravelMeters
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

struct Car
{
    s32 Ordinal;          // Unique ID of the car make/model
    s32 Class;            // Between 0 (D - lowest) and 7 (X class - highest) inclusive
    s32 PerformanceIndex; // Between 100 (lowest) and 999 (highest) inclusive
    s32 DrivetrainType;   // 0 = FWD, 1 = RWD, 2 = AWD
    s32 NumCylinders;     // Number of cylinders in the engine
    s32 Type;             // Unique ID of the car make/model
};

struct ObjectHit
{
    s8 obj1;
    s8 obj2;
    s8 obj3;
    s8 obj4;
    s8 obj5;
    s8 obj6;
};

struct Position
{
    f32 X;
    f32 Y;
    f32 Z;
};

struct TireTemp
{
    f32 FrontLeft;
    f32 FrontRight;
    f32 RearLeft;
    f32 RearRight;
};

struct Race
{
    f32 DistanceTraveled;
    f32 BestLap;
    f32 LastLap;
    f32 CurrentLap;
    f32 CurrentTime;
    u16 LapNumber;
    u8 Position;
} __attribute__((packed)); // Unaligned struct

struct VehicleControl
{
    u8 Accel;
    u8 Brake;
    u8 Clutch;
    u8 Handbrake;
    u8 Gear;
    u8 Steer;
} __attribute__((packed));

typedef struct _Telemetry
{
    s32 IsRaceOn;                                                 // 1 when race is on, 0 when in menus/race stopped
    u32 TimestampMS;                                              // Current in-game timestamp. Overflows eventually
    struct Engine Engine;                                         // RPM values from the engine
    struct Acceleration Acceleration;                             // X/Y/Z acceleration values for vehicle
    struct Velocity Velocity;                                     // X/Y/Z velocity values for vehicle
    struct AngularVelocity AngularVelocity;                       // X/Y/Z angular velocity values for vehicle
    struct Rotation Rotation;                                     // X/Y/Z rotation value for vehicle
    struct NormalizedSuspensionTravel NormalizedSuspensionTravel; // Spring extension/compression values
    struct TireSlipRatio TireSlipRatio;                           //
    struct WheelRotationSpeed WheelRotationSpeed;                 // Raw wheel rotation speed
    struct WheelOnRumbleStrip WheelOnRumbleStrip;                 // Tire rumble values
    struct WheelInPuddleDepth WheelInPuddleDepth;                 // Water depth values
    struct SurfaceRumble SurfaceRumble;                           // Full vehicle rumble values
    struct TireSlipAngle TireSlipAngle;                           //
    struct TireCombinedSlip TireCombinedSlip;                     //
    struct SuspensionTravelMeters SuspensionTravelMeters;         // How far the suspension is traveling. 0.0 means fully decompressed and 1.0 means fully compressed
    struct Car Car;                                               // Car specific info like specs and metadata
    struct ObjectHit ObjectHit;                                   // Activates when hitting breakable objects- nobody really knows what it means
    struct Position Position;                                     // Vehicle postion in the world
    f32 Speed;                                                    // Speed in meters per second
    f32 Power;                                                    // Power in watts
    f32 Torque;                                                   // Power in newtons/meter
    struct TireTemp TireTemp;                                     // Tire temperature in F for all 4 tires
    f32 Boost;                                                    // Boost gauge in PSI
    f32 Fuel;                                                     // % of much fuel you have left, only used in sim mode races
    struct Race Race;                                             // Information about the current race if you're in one
    struct VehicleControl VehicleControl;                         // Inputs received from the controller mapped to vehicle actions
    u8 NormalizedDrivingLine;                                     // Driving line follow accuracy
    u8 NormalizedAIBrakeDifference;                               //
} Telemetry;

// Raw telemetry for more explicit access by name
typedef struct _RawTelemetry
{
    s32 IsRaceOn;         
    u32 TimestampMS;      

    f32 EngineMaxRpm;     
    f32 EngineIdleRpm;    
    f32 EngineCurrentRpm; 

    f32 AccelerationX;    
    f32 AccelerationY;    
    f32 AccelerationZ;    

    f32 VelocityX;        
    f32 VelocityY;        
    f32 VelocityZ;       

    f32 AngularVelocityX;
    f32 AngularVelocityY;
    f32 AngularVelocityZ;

    f32 RotationX;
    f32 RotationY;
    f32 RotationZ;

    f32 NormalizedSuspensionTravelFrontLeft;
    f32 NormalizedSuspensionTravelFrontRight;
    f32 NormalizedSuspensionTravelRearLeft;
    f32 NormalizedSuspensionTravelRearRight;

    f32 TireSlipRatioFrontLeft;
    f32 TireSlipRatioFrontRight;
    f32 TireSlipRatioRearLeft;
    f32 TireSlipRatioRearRight;

    f32 WheelRotationSpeedFrontLeft;
    f32 WheelRotationSpeedFrontRight;
    f32 WheelRotationSpeedRearLeft;
    f32 WheelRotationSpeedRearRight;

    f32 WheelOnRumbleStripFrontLeft;
    f32 WheelOnRumbleStripFrontRear;
    f32 WheelOnRumbleStripRearLeft;
    f32 WheelOnRumbleStripRearRight;

    f32 WheelInPuddleDepthFrontLeft;
    f32 WheelInPuddleDepthFrontRight;
    f32 WheelInPuddleDepthRearLeft;
    f32 WheelInPuddleDepthRearRight;

    f32 SurfaceRumbleFrontLeft;
    f32 SurfaceRumbleFrontRight;
    f32 SurfaceRumbleRearLeft;
    f32 SurfaceRumbleRearRight;

    f32 TireSlipAngleFrontLeft;
    f32 TireSlipAngleFrontRight;
    f32 TireSlipAngleRearLeft;
    f32 TireSlipAngleRearRight;

    f32 TireCombinedSlipFrontLeft;
    f32 TireCombinedSlipFrontRight;
    f32 TireCombinedSlipRearLeft;
    f32 TireCombinedSlipRearRight;

    f32 SuspensionTravelMetersFrontLeft;
    f32 SuspensionTravelMetersFrontRight;
    f32 SuspensionTravelMetersRearLeft;
    f32 SuspensionTravelMetersRearRight;

    s32 CarOrdinal;
    s32 CarClass;
    s32 CarPerformanceIndex;
    s32 CarDrivetrainType;
    s32 CarNumCylinders;
    s32 CarType;

    s8 obj1;
    s8 obj2;
    s8 obj3;
    s8 obj4;
    s8 obj5;
    s8 obj6;

    f32 PositionX;
    f32 PositionY;
    f32 PositionZ;

    f32 Speed;
    f32 Power;
    f32 Torque;

    f32 TireTempFrontLeft;
    f32 TireTempFrontRight;
    f32 TireTempRearLeft;
    f32 TireTempRearRight;

    f32 Boost;
    f32 Fuel;

    f32 RaceDistanceTraveled;
    f32 RaceBestLap;
    f32 RaceLastLap;
    f32 RaceCurrentLap;
    f32 RaceCurrentTime;
    u16 RaceLapNumber;
    u8  RacePosition;

    u8 Accel;
    u8 Brake;
    u8 Clutch;
    u8 Handbrake;
    u8 Gear;
    u8 Steer;

    u8 NormalizedDrivingLine;
    u8 NormalizedAIBrakeDifference;
} RawTelemetry;