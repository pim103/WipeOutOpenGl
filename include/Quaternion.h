#ifndef QUATERNION_H
#define QUATERNION_H

#include "../include/Vector.h"

class Quaternion
{
    public:
        virtual ~Quaternion();
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
		void Quaternion::operator-=(const Quaternion& q);
		Quaternion operator-(const Quaternion& q) const;
		void operator*=(const Quaternion& q);
		Quaternion operator*(const Quaternion& q) const;
		Quaternion multiply(const Quaternion& q) const;
    protected:

    private:
};

#endif // QUATERNION_H
