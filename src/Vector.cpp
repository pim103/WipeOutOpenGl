#include "../include/Vector.h"
#include <cmath>
#include "../include/Quaternion.h"

Vector::Vector(float px, float py, float pz )
{
    //dtor
    x = px;
    y = py;
    z = pz;
}

Vector& Vector::operator=(const Vector& v) {

	x = v.x;
	y = v.y;
	z = v.z;

	return *this;

}

void Vector::operator+=(const Vector& v) {

	x += v.x;
	y += v.y;
	z += v.z;

}

Vector Vector::operator+(const Vector& v)const {


	return Vector(x + v.x, y + v.y, z + v.z);
}

void Vector::operator-=(const Vector & v) {

	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector Vector::operator-(const Vector & v)const {

	return Vector(x - v.x, y - v.y, z - v.z);
}

void Vector::operator*=(const float s) {

	x *= s;
	y *= s;
	z *= s;

}

Vector Vector::operator*(const float s) const {

	return Vector(s * x, s * y, s * z);
}

//divide by scalar
void Vector::operator /=(const float s) {

	x = x / s;
	y = y / s;
	z = z / s;
}

Vector Vector::operator/(const float s)const {

	return Vector(x / s, y / s, z / s);
}

float Vector::operator*(const Vector & v) const {

	return x * v.x + y * v.y + z * v.z;

}

float Vector::dot(const Vector & v) const {

	return x * v.x + y * v.y + z * v.z;

}

Vector Vector::cross(const Vector& v) const {

	return Vector(y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);

}

void Vector::normalize(){

        float mag=std::sqrt(x*x+y*y+z*z);

        if (mag>0.0f) {

            //normalize it
            float oneOverMag=1.0f/mag;

            x=x*oneOverMag;
            y=y*oneOverMag;
            z=z*oneOverMag;

        }

    }

Vector Vector::rotateVectorAboutAngleAndAxis(float uAngle, Vector& uAxis){

    //convert our vector to a pure quaternion
    Quaternion p(0,(*this));

    //normalize the axis
    uAxis.normalize();

    //create the real quaternion
    Quaternion q(uAngle,uAxis);

    //convert quaternion to unit norm quaternion
    q.convertToUnitNormQuaternion();

    //Get the inverse of the quaternion
    Quaternion qInverse=q.inverse();

    //rotate the quaternion
    Quaternion rotatedVector=q*p*qInverse;

    //return the vector part of the quaternion
    return rotatedVector.v;
}

