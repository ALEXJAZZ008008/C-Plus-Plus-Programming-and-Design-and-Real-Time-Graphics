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

Vector3d::Vector3d(double inX, double inY, double inZ)
{
	x = inX;
	y = inY;
	z = inZ;
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

const Vector3d Vector3d::Add1(const Vector3d &vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);;
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::Add2(const Vector3d &vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::Add3(const Vector3d vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::Add4(const Vector3d vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);
}

//-----------------------------------------------------------------------------

const Vector3d &Vector3d::Add5(const Vector3d &vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);
}

//-----------------------------------------------------------------------------

const Vector3d &Vector3d::Add6(const Vector3d vector) const
{
	return Vector3d(x + vector.x, y + vector.y, z + vector.z);;
}

//-----------------------------------------------------------------------------

Vector3d &Vector3d::Add7(const Vector3d &vector1, const Vector3d &vector2)
{
	*this = Vector3d (vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);

	return *this;
}

Vector3d Vector3d::Add8(const Vector3d &vector1, const Vector3d &vector2)
{
	*this = Vector3d (vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);

	return *this;
}

Vector3d &Vector3d::Add9(const Vector3d &vector1, const Vector3d &vector2)
{
	x = vector1.x + vector2.x;
	y = vector1.y + vector2.y;
	z = vector1.z + vector2.z;

	return *this;
}

//-----------------------------------------------------------------------------

const Vector3d Vector3d::Subtract(const Vector3d &vector) const
{
	return Vector3d(x - vector.x, y - vector.y, z - vector.z);
}

//-----------------------------------------------------------------------------

const double Vector3d::Distance  (const Vector3d &vector) const
{
	return static_cast<double>(sqrt(DistanceSquared(vector)));
}

const double Vector3d::DistanceSquared(const Vector3d &vector) const
{
	return Subtract(vector).LengthSquared();
}

//-----------------------------------------------------------------------------

const double Vector3d::Length() const
{
	return static_cast<double>(sqrt(LengthSquared()));
}

const double Vector3d::LengthSquared() const
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

const bool Vector3d::IsZero(double Tolerance) const
{
	return (LengthSquared() <= Tolerance * Tolerance);
}

const bool Vector3d::IsUnit(double Tolerance) const
{
	return fabs(Length() - 1.0) <= Tolerance;
}

const bool Vector3d::IsEqual(const Vector3d &vector, double Tolerance) const
{
	return Subtract(vector).IsZero(Tolerance);
}

//-----------------------------------------------------------------------------