#include "Vector3d.h"
#include <cmath>

//-----------------------------------------------------------------------------

Vector3d::Vector3d()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(double d)
{
	x = d;
	y = d;
	z = d;
}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;
}

//-----------------------------------------------------------------------------

void Vector3d::Write(ostream &stream)
{
	stream << "(" << x << "," << y << "," << z << ")" << endl;
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

double Vector3d::Distance(const Vector3d &vector) const
{
	return static_cast<double>(sqrt(DistanceSquared(vector)));
}

double Vector3d::DistanceSquared(const Vector3d &vector) const
{
	return (Subtract(vector)).LengthSquared();
}

//-----------------------------------------------------------------------------

double Vector3d::Length() const
{
	return static_cast<double>(sqrt(LengthSquared()));
}

double Vector3d::LengthSquared() const
{
	return ((x * x) + (y * y) + (z * z));
}

//-----------------------------------------------------------------------------

const Vector3d &Vector3d::Normalise()
{
	return Normalise(*this);
}

const Vector3d &Vector3d::Normalise(const Vector3d &vector)
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

bool Vector3d::IsZero(double Tolerance) const
{
	return (LengthSquared() <= (Tolerance * Tolerance));
}

bool Vector3d::IsUnit(double Tolerance) const
{
	return fabs(Length() - 1.0) <= Tolerance;
}

bool Vector3d::IsEqual(const Vector3d &vector, double Tolerance) const
{
	return Subtract(vector).IsZero(Tolerance);
}