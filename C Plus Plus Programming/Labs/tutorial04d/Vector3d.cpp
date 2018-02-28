#include "Vector3d.h"
#include <cmath>

//-----------------------------------------------------------------------------

Vector3d::Vector3d()
{
	x=0.0;
	y=0.0;
	z=0.0;
}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(double d)
{
	x=d;
	y=d;
	z=d;
}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(double X, double Y, double Z)
{
	x=X;
	y=Y;
	z=Z;
}

//-----------------------------------------------------------------------------

bool Vector3d::operator == (const Vector3d &vector) const
{
	return (fabs(x - vector.x) < V3_EPSILON) && (fabs(y - vector.y) < V3_EPSILON) && (fabs(z - vector.z) < V3_EPSILON);
}

//-----------------------------------------------------------------------------

bool Vector3d::operator != (const Vector3d &vector) const
{
	return !(*this == vector);
}

//-----------------------------------------------------------------------------

ostream &operator << (ostream &stream, const Vector3d &vector)
{
	stream << "(" << vector.x << "," << vector.y << "," << vector.z << ")" << endl;

	return stream;
}

//-----------------------------------------------------------------------------

istream &operator >> (istream &stream, const Vector3d &vector)
{
	stream >> vector.x >> vector.y >> vector.z;

	return stream;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Add(const Vector3d &vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Subtract(const Vector3d &vector) const
{
	return Vector3d(x - vector.x, y - vector.y, z - vector.z);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Multiply(const double n) const
{
	return Vector3d(n * x, n * y, n * z);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Divide(const double n) const
{
	return Vector3d(n / x, n / y, n / z);
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::operator += (const Vector3d &vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::operator -= (const Vector3d &vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::operator *= (const Vector3d &vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::operator /= (const Vector3d &vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;

	return *this;
}

//-----------------------------------------------------------------------------

Vector3d operator - (const Vector3d &vector)
{
	return Vector3d(-(vector.x), -(vector.y), -(vector.z));
}

//-----------------------------------------------------------------------------

Vector3d operator * (const double &n, const Vector3d &vector)
{
	return n * vector;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::Cross(const Vector3d &vector) const
{
	return Vector3d((y * vector.z) - (vector.z * y), (x * vector.z) - (vector.z * x), (x * vector.y) - (vector.y * x));
}

//-----------------------------------------------------------------------------

double Vector3d::Dot(const Vector3d &vector) const
{
	return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

//-----------------------------------------------------------------------------

double Vector3d::Distance(const Vector3d &vector) const
{
	return static_cast<double>(sqrt( DistanceSqr(vector)));
}

double Vector3d::DistanceSqr(const Vector3d &vector) const
{
	return Subtract(vector).LengthSqr();
}

//-----------------------------------------------------------------------------

double Vector3d::Length() const
{
	return static_cast<double>(sqrt(LengthSqr()));
}

double Vector3d::LengthSqr() const
{
	return ((x * x) + (y * y) + (z * z));
}

//-----------------------------------------------------------------------------

const Vector3d & Vector3d::Normalise()
{
	return Normalise(*this);
}

const Vector3d & Vector3d::Normalise(const Vector3d &vector)
{
	double r = vector.Length();
	if (fabs(r) > V3_EPSILON) // guard against divide by zero
	{
		return *this = Vector3d(vector.x / r, vector.y / r, vector.z / r);	// normalise and return
	}
	else
	{
		return *this;
	}
}

//-----------------------------------------------------------------------------

bool Vector3d::IsZero  (double Tolerance) const
{
	return (LengthSqr() <= Tolerance * Tolerance);
}

bool Vector3d::IsUnit (double Tolerance) const
{
	return fabs(Length() - 1.0) <= Tolerance;
}

bool Vector3d::IsEqual(const Vector3d &vector, double Tolerance) const
{
	return Subtract(vector).IsZero(Tolerance);
}

//-----------------------------------------------------------------------------