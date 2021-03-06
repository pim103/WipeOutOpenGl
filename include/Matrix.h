#ifndef MATH_MATRICES_H
#define MATH_MATRICES_H

#include <iostream>
#include <iomanip>
#include "Vector.h"

class Matrix
{
    public:
        // constructors
        Matrix();  // init with identity
        Matrix(const float src[16]);
        Matrix(float m00, float m01, float m02, float m03, // 1st column
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

    protected:

    private:
        float       getCofactor(float m0, float m1, float m2,
                                float m3, float m4, float m5,
                                float m6, float m7, float m8);

        float m[16];
        float tm[16];                                       // transpose m

};

#endif
