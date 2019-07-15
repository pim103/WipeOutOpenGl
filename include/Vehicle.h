#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include "Block.h"
#include "Quaternion.h"

class Vehicle{
    public:
        float x;
        float y;
        float z;
        float speedVehicle;
        bool lockedOnVehicle;
        float sensibility;

        float dirX;
        float dirZ;

        float angleH;
        float angleY;
        float deltaAngleX;
        int xOrigin;
        int inputRotation;
        int yOrigin;

        Block *body;
        Quaternion *quat;
        Vector *vec;
        Vector *vecAxis;

        float scaleX;
        float scaleY;
        float scaleZ;

        Vehicle();
        void UpdateVehicleMovement();
        void CreateBody();
        void DrawBody();
        void OrienterVehicle();
        void releaseDir();
        void changeDir();

    private:
    protected:
};

#endif // VEHICLE_H_INCLUDED
