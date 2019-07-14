#include <math.h>
#include <stdio.h>

#include "Block.h"
#include "Controller.h"
#include "Vehicle.h"
#include "Map.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
    #define M_PI_2 3.14159265358979323846/2
#endif

extern Map *m;

extern Controller *controller;

Vehicle::Vehicle(){
    this->x = 10.0;
    this->y = 0.0;
    this->z = 10.0;

    this->scaleX = 1.0;
    this->scaleY = 1.0;
    this->scaleZ = 2.0;

    this->sensibility = 0.005;
    this->dirX = 0.0f;
    this->dirZ = 0.0f;

    this->angleH = 0.0f;
    this->angleY = 0.0f;
    this->deltaAngleX = 0.0f;
    this->xOrigin = -1;
    this->yOrigin = -1;

    this->inputRotation = 0.0f;
    this->lockedOnVehicle = true;

    this->speedVehicle = 0.1;
}

void Vehicle::UpdateVehicleMovement()
{
    if(controller->wantToMoveForward)
    {
        //dirX += speedVehicle;
        body->posx -= dirX * speedVehicle;
        body->posz += dirZ * speedVehicle;
    }else if(controller->wantToMoveBack)
    {
        //dirX -= speedVehicle;
        body->posx += speedVehicle;
        body->posz -= speedVehicle;
    }

    if(controller->wantToMoveRight)
    {
        angleY -= 1;
        if (angleY < 0) {
            angleY = 360;
        }

        inputRotation -= 5;
        OrienterVehicle();
    }
    if(controller->wantToMoveLeft)
    {
        angleY += 1;
        if(angleY > 360) {
            angleY = 0;
        }

        inputRotation += 5;
        OrienterVehicle();
    }
}

void Vehicle::CreateBody()
{
    body = new Block(x, y, z, scaleX, scaleY, scaleZ);
    body->SetTexture(FRONT, m->CarTextures[0]);
    body->SetTexture(BACK, m->CarTextures[0]);
    body->SetTexture(TOP, m->CarTextures[0]);
    body->SetTexture(BOT, m->CarTextures[0]);
    body->SetTexture(RIGHT, m->CarTextures[0]);
    body->SetTexture(LEFT, m->CarTextures[0]);
    body->SetTexture(SPHERE, m->CarTextures[0]);
}

void Vehicle::DrawBody()
{
    /*
    int goForward = 0;
    if (controller->wantToMoveForward) {
        goForward = 1;
    } else if(controller->wantToMoveBack) {
        goForward = -1;
    } else {
        goForward = 0;
    }

    body->posx += goForward * (dirX * speedVehicle);
    body->posz += goForward * (dirZ * speedVehicle);
    */

    glPushMatrix();
        glTranslatef(body->x + body->posx, 0, body->z + body->posz);
        glRotatef(angleY, 0, 1, 0);
        glTranslatef(-(body->x + body->posx), 0, -(body->z + body->posz));
        body->Draw();
    glPopMatrix();
}

void Vehicle::OrienterVehicle()
{

    deltaAngleX = (inputRotation - xOrigin) * sensibility;
    //deltaAngleX = angleY;

    // Correction de l'angle ]-Pi; Pi[

    while (deltaAngleX + angleH > M_PI)
        deltaAngleX -= M_PI * 2;
    while (deltaAngleX + angleH < -M_PI)
        deltaAngleX += M_PI * 2;

    dirX = sin(angleH + deltaAngleX);
    dirZ = -cos(angleH + deltaAngleX);
}

void Vehicle::releaseDir()
{
    angleH += deltaAngleX;

    xOrigin = -1;
}

void Vehicle::changeDir()
{
    xOrigin = inputRotation;
}
