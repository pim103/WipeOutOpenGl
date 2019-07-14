#include "../include/Quaternion.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/Vector.h"
#define DegreesToRad(angle) angle*M_PI/180
#define RadToDegrees(angle) angle*180/M_PI

Quaternion::Quaternion(float uS,Vector& uV):s(uS),v(uV){}

void Quaternion::operator+=(const Quaternion& q) {

	s += q.s;
	v += q.v;

}

Quaternion Quaternion::operator+(const Quaternion& q)const {

	float scalar = s + q.s;
	Vector imaginary = v + q.v;

	return Quaternion(scalar, imaginary);
}

//substract
void Quaternion::operator-=(const Quaternion& q) {

	s -= q.s;
	v -= q.v;
}

Quaternion Quaternion::operator-(const Quaternion& q)const {

	float scalar = s - q.s;
	Vector imaginary = v - q.v;

	return Quaternion(scalar, imaginary);
}

//multiply
void Quaternion::operator*=(const Quaternion& q) {

	(*this) = multiply(q);
}

Quaternion Quaternion::operator*(const Quaternion& q)const {

	float scalar = s * q.s - v.dot(q.v);

	Vector imaginary = q.v * s + v * q.s + v.cross(q.v);

	return Quaternion(scalar, imaginary);

}

Quaternion Quaternion::multiply(const Quaternion& q)const {

	float scalar = s * q.s - v.dot(q.v);

	Vector imaginary = q.v * s + v * q.s + v.cross(q.v);

	return Quaternion(scalar, imaginary);

}

void Quaternion::convertToUnitNormQuaternion(){

    float angle=DegreesToRad(s);
    v.normalize();
    s=cosf(angle*0.5);
    v=v*sinf(angle*0.5);

}

Quaternion Quaternion::inverse(){

    float absoluteValue=norm();
    absoluteValue*=absoluteValue;
    absoluteValue=1/absoluteValue;

    Quaternion conjugateValue=conjugate();

    float scalar=conjugateValue.s*absoluteValue;
    Vector imaginary=conjugateValue.v*absoluteValue;

    return Quaternion(scalar,imaginary);
}

Quaternion Quaternion::conjugate(){

    float scalar=s;
    Vector imaginary=v*(-1);

    return Quaternion(scalar,imaginary);
}

float Quaternion::norm(){

    float scalar=s*s;
    float imaginary=v*v;

    return sqrt(scalar+imaginary);
}

