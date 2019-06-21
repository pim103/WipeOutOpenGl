#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

#include "Block.h"

class Vehicle{
    public:
        float x;
        float y;
        float z;

        Block *body;

        float scaleX;
        float scaleY;
        float scaleZ;

        Vehicle();
        CreateBody();
        DrawBody();
    private:
    protected:
};

#endif // VEHICLE_H_INCLUDED
