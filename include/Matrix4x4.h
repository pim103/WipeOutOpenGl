#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector.h"
#include"GL/glut.h"
class Matrix4x4
{
    public:
        // constructors
        Matrix4x4();  // init with identity
        Matrix4x4(const float src[16]);
        Matrix4x4(float m00, float m01, float m02, float m03, // 1st column
                float m04, float m05, float m06, float m07, // 2nd column
                float m08, float m09, float m10, float m11, // 3rd column
                float m12, float m13, float m14, float m15);// 4th column

        void        set(const float src[16]);
        void        set(float m00, float m01, float m02, float m03, // 1st column
                        float m04, float m05, float m06, float m07, // 2nd column
                        float m08, float m09, float m10, float m11, // 3rd column
                        float m12, float m13, float m14, float m15);// 4th column
        void        setRow(int index, const float row[4]);
        void        setRow(int index, const Vector& v);
        void        setColumn(int index, const float col[4]);
        void        setColumn(int index, const Vector& v);

        GLfloat* transformMatrixToGLFloat();

        GLfloat m[16];
        float tm[16];
    protected:

    private:
                                               // transpose m
};

#endif // MATRIX4X4_H
