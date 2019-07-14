#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector();
		Vector(float px, float py, float pz);
		Vector& operator=(const Vector& v);
		void operator+=(const Vector& v);
		Vector operator+(const Vector& v) const;
		void operator-=(const Vector& v);
		Vector operator-(const Vector& v) const;
		void operator*=(const float s);
		Vector operator*(const float s) const;
		void operator/=(const float s);
		Vector operator/(const float s) const;
		float operator*(const Vector& v) const;
		float dot(const Vector& v) const;
		Vector cross(const Vector& v) const;
        virtual ~Vector();
        float x;
        float y;
        float z;
        Vector rotateVectorAboutAngleAndAxis(float uAngle, Vector& uAxis);
        void normalize();
    protected:

    private:
};

#endif // VECTOR_H
