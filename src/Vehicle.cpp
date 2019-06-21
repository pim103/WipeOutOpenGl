#include "Block.h"
#include "Vehicle.h"
#include "Map.h"

extern Map *m;

Vehicle::Vehicle(){
    this->x = 10.0;
    this->y = 2.0;
    this->z = 10.0;

    this->scaleX = 1.0;
    this->scaleY = 1.0;
    this->scaleZ = 2.0;
}

Vehicle::CreateBody()
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

Vehicle::DrawBody()
{
    body->Draw();
}
