#ifdef __APPLE__
  #include <GLUT/glut.h>
#elif __linux__
  #include <X11/Xlib.h>
  #include <GL/gl.h>
  #include <GL/glut.h>
  #include <GL/glx.h>
#elif _WIN32
  #include <windows.h>
  #include <GL/glut.h>
  #include <SOIL.h>
#else
  #warning "OS or compiler not supported"
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "Controller.h"
#include "config.hpp"
#include "geometry.hpp"
#include "toolbox.hpp"
#include "Ship.hpp"

extern Controller *controller;

Ship Ship::shipInstance;

float _rotateReactorX;
float _rotateReactorY;

bool _doRotate;
bool _doRoll;
bool _doLooping;
bool _doImmelmann;
bool _doLateral;
float _tmpGlobal1;
float _tmpGlobal2;

GLdouble angleZ;

Ship::Ship(){
    deploy = true;
    controlLock = true;
    wingAngle = 0.0;
    throttle = IDLE;
    wingsMode = IDLE;
    reactorVelocity = DEFAULT_SPEED_ROTATION;
    cockpitOffsetBack = 0;
    cockpitOffsetFront = 0;

    this->dirX = 0.0f;
    this->dirZ = 0.0f;
    this->angleY = 0.0f;
    this->posX = 0.0f;
    this->posZ = 0.0f;

    shipSpeed = START_SPEED;
    speedx = START_SPEED;
    speedy = START_SPEED;
    speedz = START_SPEED;

    maxSpeedx = 1;
    maxSpeedy = 1;
    maxSpeedz = 1;

    leftWing = true;
    rightWing = true;
}

Ship *Ship::getInstance(){
  return &shipInstance;
}

void Ship::setCockpitOffsetFront(float val){
  printf("%f\n", val);
  cockpitOffsetFront = val;
}

void Ship::setCockpitOffsetBack(float val){
  printf("%f\n", val);
  cockpitOffsetBack = val;
}

void Ship::createCrosshair(float x, float y){
    float z = 70;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[CROSSHAIR_TX]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glBegin(GL_POLYGON);
    glColor4f(0,1,0,1);

    // glTexCoord2f(0.0,0.0);
    // glVertex3f(-1.0,-1.0,0.0);
    //
    // glTexCoord2f(1.0,0.0);
    // glVertex3f(1.0,-1.0,0.0);
    //
    // glTexCoord2f(1.0,1.0);
    // glVertex3f(1.0,1.0,0.0);
    //
    // glTexCoord2f(0.0,1.0);
    // glVertex3f(-1.0,1.0,0.0);

///////
    //Front
    glTexCoord2f(-x, -y);
    glVertex3f(-x, -y, -z);
    glTexCoord2f(-x, y);
    glVertex3f(-x, y, -z);
    glTexCoord2f(x, y);
    glVertex3f(x, y, -z);
    glTexCoord2f(x, -y);
    glVertex3f(x, -y, -z);

    glEnd();
/*
    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(0,0,-70);
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();*/
}
/* Not used
void Ship::handleThrottle(){
  Camera *camera = Camera::getInstance();
  float reactorModifier = reactorVelocity*0.04;
  float speedModifier = DEFAULT_SPEED*0.1;
  double currentEyeZModifier = camera->getEyeModifier(Z);

  switch (throttle) {
    case FAST:
      if (reactorVelocity < 5) {
        camera->setEyeModifier(Z, currentEyeZModifier-0.010);
        reactorVelocity += reactorModifier;
      }
      if(speedz < maxSpeedz) speedz += speedModifier;
    break;

    case SLOW:
      if (reactorVelocity > 0.2) {
        camera->setEyeModifier(Z, currentEyeZModifier+0.005);
        reactorVelocity -= reactorModifier;
      }
      if(speedz > DEFAULT_SPEED) speedz -= speedModifier;
    break;

    case IDLE:
      if(speedz <= START_SPEED){
        if (reactorVelocity < 5) {
          reactorVelocity += reactorModifier;
        }
        speedz += speedModifier;
      }

      if(speedz >= START_SPEED){
        if (reactorVelocity > 0.2) {
          reactorVelocity -= reactorModifier;
        }
         speedz -= speedModifier;
      }

      if (currentEyeZModifier <= -0.02) {
        camera->setEyeModifier(Z, currentEyeZModifier+0.02);
      }else if (currentEyeZModifier >= 0.02) {
        camera->setEyeModifier(Z, currentEyeZModifier-0.02);
      }
      break;
  }
}
*/
void Ship::setControlLock(bool state){
  controlLock = state;
}

bool Ship::isLocked(){
  return controlLock;
}
/*
void Ship::handleWingsAnimation() {

    switch (wingsMode) {
      case FAST:
        deploy = false;
        break;

      case SLOW:
        deploy = true;
        break;

      case IDLE:
        deploy = true;
        break;
    }
}
*/
void Ship::autoRotate(){
  static double angle = 0;

  if (_doRotate) angle += 0.1;

  glRotatef(angle, 0.0, 1.0, 0.0);
}

void Ship::Roll(){
    static float barrelAngle = 0;

    if (controller->_doRoll != 0){
        barrelAngle += controller->_doRoll * 2;

        if(barrelAngle > 16) {
            barrelAngle = 16;
        } else if(barrelAngle < -16) {
            barrelAngle = -16;
        }
    } else {
        if(barrelAngle > 0) {
            barrelAngle -= 2;
        } else if(barrelAngle < 0) {
            barrelAngle += 2;
        }
    }

    glRotatef(barrelAngle, 0.0, 0.0, 1.0);
}

void Ship::looping(){
  static float loopingAngle = 0;

  if (_doLooping){
     loopingAngle += 2;
     if (loopingAngle > 360) {
       _doLooping = false;
       loopingAngle = 0;
     }
  }

  glRotatef(loopingAngle, 1.0, 0.0, 0.0);
}

// NOT IN A SCROLLER :'(
void Ship::immelmann(){
  bool loop = true;
  static float loopingAngle = 0;
  static float recoveryAngle = 0;

  if (_doImmelmann){
    if (loop && loopingAngle < 180) {
      loopingAngle += 2;
    }

     if (recoveryAngle < 180) {
       recoveryAngle += 1;
     }

     if (recoveryAngle >= 180 && loopingAngle >= 180) {
       _doImmelmann = false;
       //loopingAngle = 0;
       //recoveryAngle = 0;
     }
  }

  glRotatef(loopingAngle, 1.0, 0.0, 0.0);
  glRotatef(recoveryAngle, 0.0, 0.0, 1.0);
}

void Ship::lateralPresentation(){
  static bool down = false;
  static bool recoverTop = true;
  static bool recoverFinal = false;
  static bool finish = false;
  static float loopingAngle = 0;
  static float recoveryAngle = 0;


  if (_doLateral){
    if (!down) {
      if (loopingAngle < 90) {
        loopingAngle += 2;
      }

       if (recoveryAngle < 90) {
         recoveryAngle += 1;
       }else{
         down = true;
       }
    }

    if (down) {
      if (recoverTop) {
        if (loopingAngle > -90) {
          loopingAngle -= 2;
        }else{
          recoverTop = false;
          recoverFinal = true;
        }

      }else if(recoverFinal){
        if(recoveryAngle > 0){
          recoveryAngle -= 2;
        }else{
          finish = true;
        }

        if(loopingAngle < 0){
          loopingAngle += 1;
        }

      }else if(finish){
        _doLateral = false;
        loopingAngle = 0;
        recoveryAngle = 0;
        down = false;
        recoverTop = true;
        recoverFinal = false;
        finish = false;
      }
     }
  }

  glRotatef(loopingAngle, 1.0, 0.0, 0.0);
  glRotatef(recoveryAngle, 0.0, 0.0, 1.0);
}

ShoulderPart Ship::createShoulderPart(float minx, float miny, float minz, float width, float height, float depth){
  ShoulderPart sp;

  sp.minx = minx;
  sp.miny = miny;
  sp.minz = minz;
  sp.width = width;
  sp.height = height;
  sp.depth = depth;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textures[SHOULDER_TX]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  createPyramid(empty, minx, minx+width, miny, miny+height, minz, minz+depth);

  return sp;
}

Shoulder Ship::createLeftShoulder(CorePart frontPrd, CorePart backPrd){
  Shoulder shoulder;

  glPushMatrix();
  glScalef(0.5,3,1.3);
  glTranslatef(-(frontPrd.minx+frontPrd.width)/2,-(frontPrd.miny+frontPrd.height)*0.2,-(frontPrd.minz+frontPrd.depth)*0.8);
  glColor3f(0.0,0.1,0.8);
  glRotatef(45.0, 0.0, -1.0,0.0);
  //                         minx, miny, minz, width(x), height(y), depth(z)
  shoulder.topShoulder = createShoulderPart(frontPrd.minx, frontPrd.miny, frontPrd.minz, 1,1,1);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5,2.5,1.3);
  glTranslatef(-(frontPrd.minx+frontPrd.width)*1.9,-(frontPrd.miny+frontPrd.height)*0.205,-(frontPrd.minz+frontPrd.depth)*0.8);
  glColor3f(0.0,0.1,0.8);
  glRotatef(45.0, 0.0, 1.0,0.0);
  //                         minx, miny, minz, width(x), height(y), depth(z)
  shoulder.bottomShoulder = createShoulderPart(shoulder.topShoulder.minx, shoulder.topShoulder.miny, shoulder.topShoulder.minz, shoulder.topShoulder.width, -shoulder.topShoulder.height*0.5, shoulder.topShoulder.depth);
  glPopMatrix();

  return shoulder;
}

Shoulder Ship::createRightShoulder(CorePart frontPrd, CorePart backPrd){
  Shoulder shoulder;

  glPushMatrix();
  glScalef(0.5,3,1.3);
  glTranslatef((frontPrd.minx+frontPrd.width)*3.31,-(frontPrd.miny+frontPrd.height)*0.2,-(frontPrd.minz+frontPrd.depth)*1.6);
  glColor3f(0.0,0.1,0.8);
  glRotatef(45.0, 0.0, -1.0,0.0);
  //                         minx, miny, minz, width(x), height(y), depth(z)
  shoulder.topShoulder = createShoulderPart(-frontPrd.minx, frontPrd.miny, frontPrd.minz, 1,1,1);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5,2.5,1.3);
  glTranslatef((frontPrd.minx+frontPrd.width)*1.9,-(frontPrd.miny+frontPrd.height)*0.205,-(frontPrd.minz+frontPrd.depth)*0.2);
  glColor3f(0.0,0.1,0.8);
  glRotatef(45.0, 0.0, 1.0,0.0);
  //                         minx, miny, minz, width(x), height(y), depth(z)
  shoulder.bottomShoulder = createShoulderPart(shoulder.topShoulder.minx, shoulder.topShoulder.miny, shoulder.topShoulder.minz, shoulder.topShoulder.width, -shoulder.topShoulder.height*0.5, shoulder.topShoulder.depth);
  glPopMatrix();

  return shoulder;
}

Shoulders Ship::createShoulders(CorePart frontPrd, CorePart backPrd){
  Shoulders shoulders;
  shoulders.leftShoulder = createLeftShoulder(frontPrd, backPrd);
  shoulders.rightShoulder = createRightShoulder(frontPrd, backPrd);

  return shoulders;
}

WingPart Ship::createWingPart(float minx, float miny, float minz, float width, float height, float depth){
  WingPart wp;

  wp.minx = minx;
  wp.miny = miny;
  wp.minz = minz;
  wp.width = width;
  wp.height = height;
  wp.depth = depth;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textures[WING_TX]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  createPyramid(empty, minx, minx+width, miny, miny+height, minz, minz+depth);

  return wp;
}

Wing Ship::createLeftWing(CorePart frontPrd, CorePart backPrd, float angle){
    Wing wing;
    wing.isHit = false;

    glPushMatrix();
        glScalef(2.5,0.01,1.5);
        glTranslatef(-0.12, 0,-0.92);
        glColor3f(0.5,0.5,0.5);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        //                         minx, miny, minz, width(x), height(y), depth(z)
        wing.firstWingPart = createWingPart(frontPrd.minx, 0, frontPrd.minz, 1,1,1);
    glPopMatrix();

    // Wing deployement
    glPushMatrix();
        //glPushMatrix();
        //glTranslatef(frontPrd.minx+1,0,frontPrd.minz);
        //glRotatef(-wingAngle/10.0, 0.0 , 1.0, 0.0);
      //  glTranslatef(-frontPrd.minx-1,0,-frontPrd.minz);
        //glPopMatrix();

        glPushMatrix();
            glScalef(1.1,0.005,0.6);
            glTranslatef(-2.56,0,-1.04);
            glColor3f(0.5,0.5,0.5);
            glRotatef(120.0-wingAngle, 0.0, 1.0, 0.0);
            glRotatef(90.0, 0.0, 0.0, 1.0);
            //glTranslatef(frontPrd.minx,2,frontPrd.minz);
            //glRotatef(wingAngle, 0.0 , 1.0, 0.0);
          //  glTranslatef(-frontPrd.minx,-2,-frontPrd.minz);

            //                         minx, miny, minz, width(x), height(y), depth(z)
            wing.secondWingPart = createWingPart(frontPrd.minx, 0, frontPrd.minz, 1,1.2,1);
        glPopMatrix();

        glPushMatrix();
            glScalef(1,0.005,3.5);
            glTranslatef(-2.8,-1,-0.18);
            glColor3f(0.5,0.5,0.5);
            glRotatef(90.0-wingAngle, 0.0, 1.0, 0.0);
            glRotatef(90.0, 0.0, 0.0, 1.0);
            //                         minx, miny, minz, width(x), height(y), depth(z)
            wing.thirdWingPart = createWingPart(frontPrd.minx, 0, frontPrd.minz, 1,1.2,1);
        glPopMatrix();
    glPopMatrix();

    return wing;
}

Wing Ship::createRightWing(CorePart frontPrd, CorePart backPrd, float angle){
    Wing wing;

    glPushMatrix();
        glScalef(2.5,0.01,1.5);
        glTranslatef(-0.10, 0,-0.98);
        glColor3f(0.5,0.5,0.5);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        //                         minx, miny, minz, width(x), height(y), depth(z)
        wing.firstWingPart = createWingPart(frontPrd.minx, frontPrd.miny, frontPrd.minz, 1,-0.9,1);
    glPopMatrix();

    // Wing deployement
    glPushMatrix();
        glRotatef(0.0, 0.0 , 1.0, 0.0);

        glPushMatrix();
            glScalef(1.1,0.005,0.6);
            glTranslatef(2.77,-1,-0.66);
            glColor3f(0.5,0.5,0.5);
            glRotatef(-120.0+wingAngle, 0.0, 1.0, 0.0);
            glRotatef(-90.0, 0.0, 0.0, 1.0);
            //                         minx, miny, minz, width(x), height(y), depth(z)
            wing.secondWingPart = createWingPart(frontPrd.minx, frontPrd.miny, frontPrd.minz, 1,1.2+1,1);
        glPopMatrix();

        glPushMatrix();
            glScalef(1,0.005,3.5);
            glTranslatef(3.29,-1,0.28);
            glColor3f(0.5,0.5,0.5);
            glRotatef(-90.0+wingAngle, 0.0, 1.0, 0.0);
            glRotatef(-90.0, 0.0, 0.0, 1.0);
            //                         minx, miny, minz, width(x), height(y), depth(z)
            wing.thirdWingPart = createWingPart(frontPrd.minx, frontPrd.miny, frontPrd.minz, 1,1.2,1);
        glPopMatrix();
    glPopMatrix();

    return wing;
}

Wings Ship::createWings(CorePart frontPrd, CorePart backPrd){
  Wings wings;

  switch (wingsMode) {
    case FAST:
      deploy = false;
      if (wingAngle > 0) {
        wingAngle -= 0.5;
      }
      break;

    case SLOW:
      deploy = true;
      if (wingAngle < 16) {
        wingAngle += 0.5;
      }

      break;

    case IDLE:
      deploy = true;
      if (wingAngle < 8) {
        wingAngle += 0.5;
      }else if (wingAngle > 8) {
        wingAngle -= 0.5;
      }

      break;
  }

  if(leftWing) wings.leftWing = createLeftWing(frontPrd, backPrd, wingAngle);
  if(rightWing) wings.rightWing = createRightWing(frontPrd, backPrd, wingAngle);

  return wings;
}

CockpitPart Ship::createCockpitPart(float minx, float miny, float minz, float width, float height, float depth){
  CockpitPart cp;

  cp.minx = minx;
  cp.miny = miny;
  cp.minz = minz;
  cp.width = width;
  cp.height = height;
  cp.depth = depth;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textures[COCKPIT_TX]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  createPyramid(empty, minx, minx+width, miny, miny+height, minz, minz+depth);
  return cp;
}

CorePart Ship::createCorePart(float minx, float miny, float minz, float width, float height, float depth){
  CorePart cp;

  cp.minx = minx;
  cp.miny = miny;
  cp.minz = minz;
  cp.width = width;
  cp.height = height;
  cp.depth = depth;

  glBindTexture(GL_TEXTURE_2D, textures[CORE_TX]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  createPyramid(empty, minx, minx+width, miny, miny+height, minz, minz+depth);
  return cp;
}

Core Ship::createCore(){
    Core core;

    core.isHit = false;

    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(45.0, 0.0,1.0,0.0);
    //                         minx, miny, minz, width(x), height(y), depth(z)
    core.frontPrd = createCorePart(-0.5, -0.5, 0.0, 1.0, -2.3, 1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(45.0, 0.0,1.0,0.0);
    // minx, miny, minz, width(x), height(y), depth(z)
    core.backPrd = createCorePart(core.frontPrd.minx, core.frontPrd.miny, core.frontPrd.minz, core.frontPrd.width, 0.8, core.frontPrd.depth);
    glPopMatrix();

    return core;
}

Cockpit Ship::createCockpit(CorePart frontPrd, CorePart backPrd){
  Cockpit cockpit;

  glPushMatrix();
  glScalef(0.7,1.0,1.0);
  glColor3f(0.5,0.5,0.5);
  glTranslatef(0.45,-(frontPrd.miny+frontPrd.height)*0.2,0.42-cockpitOffsetBack);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(45.0, 0.0,1.0,0.0);
//                         minx, miny, minz, width(x), height(y), depth(z)
  cockpit.frontPrd = createCockpitPart(frontPrd.minx, frontPrd.miny, frontPrd.minz, frontPrd.width*0.6, backPrd.height*1.8, frontPrd.depth*0.6);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.75,1.0,1.0);
  glColor3f(0.5,0.5,0.5);
  glTranslatef(0.4,(-(frontPrd.miny+frontPrd.height)*0.2)-(0.30-cockpitOffsetFront),-(frontPrd.minz+frontPrd.depth));
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(45.0, 0.0,1.0,0.0);
  // minx, miny, minz, width(x), height(y), depth(z)
  cockpit.backPrd = createCockpitPart(cockpit.frontPrd.minx, -cockpit.frontPrd.miny, cockpit.frontPrd.minz, cockpit.frontPrd.width, -0.5, cockpit.frontPrd.depth);
  glPopMatrix();

  return cockpit;
}

Core Ship::createBottomCore(CorePart frontPrd, CorePart backPrd){
  glTranslatef(0.05,-0.48,0.0);
  glScalef(0.85,0.6,0.6);
  CorePart cp1;
  CorePart cp2;
  Core core;

  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(45.0, 0.0,1.0,0.0);
  cp1 = createCorePart(frontPrd.minx, frontPrd.miny, frontPrd.minz, frontPrd.width, frontPrd.height, frontPrd.depth);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.5,0.5,0.5);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glRotatef(45.0, 0.0,1.0,0.0);
  cp2 = createCorePart(backPrd.minx, backPrd.miny, backPrd.minz, backPrd.width, backPrd.height*2.0, backPrd.depth);
  glPopMatrix();

  return core;
}

void Ship::createReactor(){

  glutWireCube(0.25);
  glutWireSphere(0.06, 4, 4);

}

void Ship::animateReactor(){
  //handleThrottle();
  //handleWingsAnimation();
  //rotateReactorX += reactorVelocity;
  //rotateReactorY += reactorVelocity;

  glColor3f(1,1,1);
  glTranslatef(0.34, -0.28, 0.53);
  glRotatef(rotateReactorX, 1,0,0);
  glRotatef(rotateReactorY, 0,1,0);
}

void Ship::display(){
    glPushMatrix();
        glTranslatef(posX, 0, posZ);
        glRotatef(angleY, 0, 1, 0);

        // ANIMATE
        autoRotate();
        Roll();
        looping();
        immelmann();
        lateralPresentation();

        glPushMatrix();
            animateReactor();
            createReactor();
        glPopMatrix();

      // DRAW
      // CORE
      core = createCore();

      // COCKPIT
      cockpit = createCockpit(core.frontPrd, core.backPrd);

      // BOTTOM CORE
      bottomCore = createBottomCore(core.frontPrd, core.backPrd);

      shoulders = createShoulders(core.frontPrd, core.backPrd);

      wings = createWings(core.frontPrd, core.backPrd);

      createCrosshair(0.5,0.5);

  glPopMatrix();
}

void Ship::loadTexture(){
  textures[CROSSHAIR_TX] = SOIL_load_OGL_texture("textures/crosshair_sm.bmp",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  textures[CORE_TX] = SOIL_load_OGL_texture("textures/core.bmp",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  textures[COCKPIT_TX] = SOIL_load_OGL_texture("textures/txt.bmp",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  textures[WING_TX] = SOIL_load_OGL_texture("textures/core.bmp",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  textures[SHOULDER_TX] = SOIL_load_OGL_texture("textures/core.bmp",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void Ship::hitLeftWing() {
  setLeftWingStatus(true);
}

void Ship::hitRightWing() {
  setRightWingStatus(true);
}

void Ship::hitCore() {
  setCoreStatus(true);
}

float Ship::getSpeedX()
{
    return speedx;
}
float Ship::getSpeedY()
{
    return speedy;
}
float Ship::getSpeedZ()
{
    return speedz;
}

void Ship::setSpeedX(float speed)
{
    speedx = speed;
}
void Ship::setSpeedY(float speed)
{
    speedy = speed;
}
void Ship::setSpeedZ(float speed)
{
    speedz = speed;
}

float Ship::getMaxSpeedX()
{
    return maxSpeedx;
}
float Ship::getMaxSpeedY()
{
    return maxSpeedy;
}
float Ship::getMaxSpeedZ()
{
    return maxSpeedz;
}

float Ship::getThrottle(){
  return throttle;
}

void Ship::setThrottle(int id) {
  throttle = id;
}

void Ship::setRightWing(bool destroy) {
  rightWing = destroy;
}

void Ship::setLeftWing(bool destroy) {
  leftWing = destroy;
}

bool Ship::getLeftWing()
{
    return leftWing;
}

bool Ship::getRightWing()
{
    return rightWing;
}

void Ship::animWings(int id){
  wingsMode = id;
}

bool Ship::getCoreStatus(){
  return core.isHit;
}

bool Ship::getLeftWingStatus(){
  return wings.leftWing.isHit;
}

bool Ship::getRightWingStatus(){
  return wings.rightWing.isHit;
}

void Ship::setCoreStatus(bool status){
  core.isHit = status;
}

void Ship::setLeftWingStatus(bool status){
  wings.leftWing.isHit = status;
}

void Ship::setRightWingStatus(bool status){
  wings.rightWing.isHit = status;
}

void Ship::UpdateVehicleMovement()
{
    if(controller->wantToMoveForward)
    {
        posX -= dirX * shipSpeed;
        posZ += dirZ * shipSpeed;
    }else if(controller->wantToMoveBack)
    {
        posX += dirX * shipSpeed;
        posZ -= dirZ * shipSpeed;
    }

    if(controller->wantToMoveRight)
    {
        angleY -= 2;
        if (angleY < 0) {
            angleY = 360;
        }

        OrienterVehicle();
    }
    if(controller->wantToMoveLeft)
    {
        angleY += 2;
        if(angleY > 360) {
            angleY = 0;
        }

        OrienterVehicle();
    }
}

void Ship::OrienterVehicle()
{
    dirX = sin(angleY * (M_PI / 180));
    dirZ = -cos(angleY * (M_PI/180));
}

/*
void Ship::checkIntegrity()
{
    if(!leftWing && !rightWing)
    {
        scene.translateX += (float)(rand()%10 - 5);
        scene.translateY += (float)(rand()%10 - 5);
        angleZ += (GLdouble)(rand()%10 - 5);
    }
    else if(!leftWing)
    {
        angleZ += (GLdouble)(rand()%5 + 1);
    }
    else if(!rightWing)
    {
        angleZ -= (GLdouble)(rand()%5 + 1);
    }
}
*/
