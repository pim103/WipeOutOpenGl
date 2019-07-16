#include "../include/Quaternion.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/Vector.h"
#include "../include/Matrix4x4.h"
#define DegreesToRad(angle) angle*M_PI/180
#define RadToDegrees(angle) angle*180/M_PI

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
    #define M_PI_2 3.14159265358979323846/2
#endif

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

Matrix4x4 Quaternion::createMatrix()
{
	Matrix4x4 out;

	/*// First column
	out.m[0] = 1.0f - 2.0f*v.y*v.y - 2.0f*v.z*v.z;
	out.m[1] = 2.0f*v.x*v.y - 2.0f*v.z*s;
	out.m[2] = 2.0f*v.x*v.z + 2.0f*v.y*s;
	out.m[3] = 0.0f;

	// Second column
	out.m[4] = 2.0f*v.x*v.y + 2.0f*v.z*s;
	out.m[5] = 1.0f - 2.0f*v.x*v.x - 2.0f*v.z*v.z;
	out.m[6] = 2.0f*v.y*v.z - 2.0f*v.x*s;
	out.m[7] = 0.0f;

	// Third column
	out.m[8] = 2.0f*v.x*v.z - 2.0f*v.y*s;
	out.m[9] = 2.0f*v.y*v.z + 2.0f*v.x*s;
	out.m[10] = 1.0f - 2.0f*v.x*v.x - 2.0f*v.y*v.y;
	out.m[11] = 0.0f;

	// Fourth column
	out.m[12] = 0;
	out.m[13] = 0;
	out.m[14] = 0;
	out.m[15] = 1.0f;*/

	out.m[0]=2*(s*s + v.x*v.x)-1;
    out.m[4]=2*(v.x*v.y - s*v.z);
    out.m[8]=2*(v.x*v.z + s*v.y);
    out.m[12]=0.0f;

    out.m[1]=2*(v.x*v.y + s*v.z);
    out.m[5]=2*(s*s + v.y*v.y)-1;
    out.m[9]=2*(v.y*v.z - s*v.x);
    out.m[13]=0.0f;

    out.m[2]=2*(v.x*v.z - s*v.y);
    out.m[6]=2*(v.y*v.z + s*v.x);
    out.m[10]=2*(s*s + v.z*v.z)-1;
    out.m[14]=0.0f;

    out.m[3]=0.0f;
    out.m[7]=0.0f;
    out.m[11]=0.0f;
    out.m[15]=1.0f;

	return out;
}

