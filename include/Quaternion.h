#ifndef QUATERNION_H
#define QUATERNION_H

#include "../include/Vector.h"
#include "../include/Matrix4x4.h"
#include <stdio.h>


class Quaternion
{
    public:
        float s;

        //vector
        Vector v;


        //Constructor
        Quaternion(float uS,Vector& uV);
        void convertToUnitNormQuaternion();
        Quaternion inverse();
        Quaternion conjugate();
        float norm();

		//operators
		void operator+=(const Quaternion& q);
		Quaternion operator+(const Quaternion& q) const;
		void operator-=(const Quaternion& q);
		Quaternion operator-(const Quaternion& q) const;
		void operator*=(const Quaternion& q);
		Quaternion operator*(const Quaternion& q) const;
		Quaternion multiply(const Quaternion& q) const;
		Matrix4x4 createMatrix();
    protected:

    private:
};

#endif // QUATERNION_H
