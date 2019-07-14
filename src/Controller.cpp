#include <stdlib.h>

#include "Vehicle.h"
#include "Controller.h"

extern Vehicle *v;

Controller::Controller()
{
    this->wantToMoveForward = false;
    this->wantToMoveBack = false;
    this->wantToMoveLeft = false;
    this->wantToMoveRight = false;
}

void Controller::GetPlayerIntent(unsigned char key){
    switch(key) {
        case 'v':
            v->lockedOnVehicle = !v->lockedOnVehicle;
            break;
        case 'z':
            wantToMoveForward = true;
            break;
        case 'q':
            wantToMoveLeft = true;
            v->changeDir();
            break;
        case 's':
            wantToMoveBack = true;
            break;
        case 'd':
            wantToMoveRight = true;
            v->changeDir();
            break;
    }
}

void Controller::ReleasePlayerIntent(unsigned char key){
    switch(key) {
        case 'z':
            wantToMoveForward = false;
            v->releaseDir();
            break;
        case 'q':
            wantToMoveLeft = false;
            v->releaseDir();
            break;
        case 's':
            wantToMoveBack = false;
            v->releaseDir();
            break;
        case 'd':
            wantToMoveRight = false;
            v->releaseDir();
            break;
    }
}
