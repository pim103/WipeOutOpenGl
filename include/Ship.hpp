#ifndef SHIP_HPP_INCLUDED
#define SHIP_HPP_INCLUDED

#define DEFAULT_SPEED_ROTATION 0.5
#define START_SPEED 0.5
#define DEFAULT_SPEED 0.1 // Lowest speed

#include "Vector.h"
#include "Quaternion.h"

enum{IDLE, FAST, SLOW};

enum {
  CROSSHAIR_TX,
  CORE_TX,
  COCKPIT_TX,
  WING_TX,
  SHOULDER_TX,
  MAX_TX
};

typedef struct Crosshair{
  float width;
  float height;
} Crosshair;

typedef struct CorePart{
  // 4 faces of 4 vertices of 3 points in space
  float width;
  float height;
  float depth;
  float minx;
  float miny;
  float minz;
  // texture
}CorePart;

typedef struct Core{
  CorePart frontPrd;
  CorePart backPrd;
  bool isHit;
}Core;

typedef struct CockpitPart{
  // 4 faces of 4 vertices of 3 points in space
  float width;
  float height;
  float depth;
  float minx;
  float miny;
  float minz;
  // texture

}CockpitPart;

typedef struct Cockpit{
  CockpitPart frontPrd;
  CockpitPart backPrd;
}Cockpit;

typedef struct WingPart{
  // 5 faces of 5 vertices of 3 points in space
  float width;
  float height;
  float depth;
  float minx;
  float miny;
  float minz;
}WingPart;

typedef struct Wing{
  WingPart firstWingPart;
  WingPart secondWingPart;
  WingPart thirdWingPart;
  bool isHit;
}Wing;


typedef struct Wings{
  Wing leftWing;
  Wing rightWing;
}Wings;

typedef struct ShoulderPart{
  // 5 faces of 5 vertices of 3 points in space
  float width;
  float height;
  float depth;
  float minx;
  float miny;
  float minz;
}ShoulderPart;

typedef struct Shoulder{
  ShoulderPart topShoulder;
  ShoulderPart bottomShoulder;
}Shoulder;

typedef struct Shoulders{
  Shoulder leftShoulder;
  Shoulder rightShoulder;
}Shoulders;

class Ship{
  public:
  Ship();
  static Ship *getInstance();
  void display();
  void loadTexture();

  void deployWings();
  void stopDeploy();

  void animWings(int id);

  bool getLeftWingStatus();
  bool getRightWingStatus();
  bool getCoreStatus();

  void setLeftWingStatus(bool status);
  void setRightWingStatus(bool status);
  void setCoreStatus(bool status);

  void hitCore();
  void hitLeftWing();
  void hitRightWing();

  float getThrottle();

  void setThrottle(int id);

  float getSpeedX();
  float getSpeedY();
  float getSpeedZ();

  float getMaxSpeedX();
  float getMaxSpeedY();
  float getMaxSpeedZ();

  bool getLeftWing();
  bool getRightWing();
  void setLeftWing(bool isDestroyed);
  void setRightWing(bool isDestroyed);

  void setSpeedX(float speed);
  void setSpeedY(float speed);
  void setSpeedZ(float speed);

  void setControlLock(bool state);

  bool isLocked();

  void setCockpitOffsetFront(float val);
  void setCockpitOffsetBack(float val);
  void checkIntegrity();

  // New Inherit Controller
  void UpdateVehicleMovement();
  void OrienterVehicle();

  float posX;
  float posZ;
  float dirX;
  float dirZ;

  private:
  static Ship shipInstance;
  float cockpitOffsetFront;
  float cockpitOffsetBack;
  bool deploy;
  bool retract;
  bool controlLock;
  float wingAngle;
  int throttle;
  int wingsMode;

  float shipSpeed;

  float angleY;

  int textures[MAX_TX];
  // Bottom core
  Core createBottomCore(CorePart frontPrd, CorePart backPrd);

  // Core
  Core createCore();
  CorePart createCorePart(float basex, float basey, float basez, float width, float height, float depth);

  // Cockpit
  Cockpit createCockpit(CorePart frontPrd, CorePart backPrd);
  CockpitPart createCockpitPart(float basex, float basey, float basez, float width, float height, float depth);

  // Wings
  WingPart createWingPart(float basex, float basey, float basez, float width, float height, float depth);
  Wing createLeftWing(CorePart frontPrd, CorePart backPrd, float angle);
  Wing createRightWing(CorePart frontPrd, CorePart backPrd, float angle);
  Wings createWings(CorePart frontPrd, CorePart backPrd);

  // Shoulder
  ShoulderPart createShoulderPart(float basex, float basey, float basez, float width, float height, float depth);
  Shoulder createLeftShoulder(CorePart frontPrd, CorePart backPrd);
  Shoulder createRightShoulder(CorePart frontPrd, CorePart backPrd);
  Shoulders createShoulders(CorePart frontPrd, CorePart backPrd);

  // Crosshair
  void createCrosshair(float x, float y);

  // Reactor
  void createReactor();
  void animateReactor();

  // Animation
  void autoRotate();
  void Roll();
  void looping();
  void immelmann();
  void lateralPresentation();
  void handleThrottle();
  void handleWingsAnimation();
  Core bottomCore;
  Core core;
  Cockpit cockpit;
  Wings wings;
  Shoulders shoulders;
  float reactorVelocity;
  float rotateReactorX;
  float rotateReactorY;

  float speedx;
  float speedy;
  float speedz;

  float maxSpeedx;
  float maxSpeedy;
  float maxSpeedz;

  bool rightWing;
  bool leftWing;
  Vector *vec;
  Quaternion *quat;
  Vector *vecRoll;
  Quaternion *quatRoll;
  void RotateWithQuaternion(float angle);
  void BarrelRollWithQuaternion(float angle);
};

#endif // SHIP_HPP_INCLUDED
