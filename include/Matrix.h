#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include "Vector.h"


class Matrix{

private:

public:

    float matrixData[9]={0.0};

    Matrix();
    Matrix(float m0,float m3,float m6,float m1,float m4,float m7,float m2,float m5,float m8);
    ~Matrix();
    Matrix operator+(const Matrix &m) const;
    void operator+=(const Matrix &m);
    Matrix operator*(const float s) const;
    void operator*=(const float s);
    Vector operator*(const Vector & v) const;
    Vector transformVectorByMatrix(const Vector& v) const;
    Matrix operator*(const Matrix& m) const;
    void operator*=(const Matrix& m);
    Matrix& operator=(const Matrix& value);
    void setMatrixAsIdentityMatrix();
    void setMatrixAsInverseOfGivenMatrix(const Matrix& m);
    Matrix getInverseOfMatrix() const;
    void invertMatrix();
    float getMatrixDeterminant() const;
    void setMatrixAsTransposeOfGivenMatrix(const Matrix& m);
    Matrix getTransposeOfMatrix() const;
    void invertAndTransposeMatrix();
    void makeRotationMatrixAboutXAxisByAngle(float uAngle);
    void makeRotationMatrixAboutYAxisByAngle(float uAngle);
    void makeRotationMatrixAboutZAxisByAngle(float uAngle);
    void transformMatrixAboutXAxisByAngle(float uAngle);
    void transformMatrixAboutYAxisByAngle(float uAngle);
    void transformMatrixAboutZAxisByAngle(float uAngle);
    void show();

};
#endif /* Matrix_hpp */
