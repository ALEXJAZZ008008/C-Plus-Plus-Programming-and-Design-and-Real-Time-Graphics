#include "Vector3d.h"
#include <cmath>

Vector3d::Vector3d()
{
	m_x=0.0;
	m_y=0.0;
	m_z=0.0;
}

Vector3d::Vector3d(double d)
{

	m_x=d;
	m_y=d;
	m_z=d;
}

Vector3d::Vector3d(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3d::Vector3d(const Vector3d &vector)
{
	cout << "Copy constructor called" << endl;
}

Vector3d &Vector3d::operator = (const Vector3d &vector)
{
	cout << "Assignment operator called" << endl;

	return *this;
}

bool Vector3d::operator == (const Vector3d &V) const
{
	return (fabs(m_x - V.m_x) < V3_EPSILON) && (fabs(m_y - V.m_y) < V3_EPSILON) && (fabs(m_z - V.m_z) < V3_EPSILON);
}

bool Vector3d::operator != (const Vector3d &V) const
{
	return !(*this == V);
}

Vector3d Vector3d::Add1(const Vector3d &R) const
{
	cout << "Add1 called" << endl;

	Vector3d v(m_x + R.m_x, m_y + R.m_y, m_z + R.m_z);

	return v; 
}

Vector3d Vector3d::Add2(const Vector3d &R) const
{
	cout << "Add2 called" << endl;

	return Vector3d(m_x + R.m_x, m_y + R.m_y, m_z + R.m_z);
}

Vector3d Vector3d::Add3(const Vector3d R) const
{
	cout << "Add3 called" << endl;

	Vector3d v(m_x + R.m_x, m_y + R.m_y, m_z + R.m_z);

	return v;
}

Vector3d Vector3d::Add4(const Vector3d R) const
{
	cout << "Add4 called" << endl;

	return Vector3d (m_x + R.m_x, m_y + R.m_y, m_z + R.m_z);
}

Vector3d &Vector3d::Add5(const Vector3d &R) const
{
	cout << "Add5 called" << endl;

	return Vector3d (m_x + R.m_x, m_y + R.m_y, m_z + R.m_z);
}

Vector3d &Vector3d::Add6(const Vector3d R) const
{
	cout << "Add6 called" << endl;

	Vector3d v(m_x + R.m_x, m_y + R.m_y, m_z + R.m_z);

	return v;
}

Vector3d &Vector3d::Add7(const Vector3d& L, const Vector3d& R) 
{
	cout << "Add7 called" << endl;

	*this = Vector3d (L.m_x + R.m_x, L.m_y + R.m_y, L.m_z + R.m_z);

	return *this;
}

Vector3d Vector3d::Add8(const Vector3d& L, const Vector3d& R) 
{
	cout << "Add8 called" << endl;

	*this = Vector3d (L.m_x + R.m_x, L.m_y + R.m_y, L.m_z + R.m_z);

	return *this;
}

Vector3d &Vector3d::Add9(const Vector3d& L, const Vector3d& R) 
{
	cout << "Add9 called" << endl;

	m_x = L.m_x + R.m_x;
	m_y = L.m_y + R.m_y;
	m_z = L.m_z + R.m_z;

	return *this;
}

Vector3d Vector3d::Subtract(const Vector3d &R) const
{
	return Vector3d(m_x - R.m_x, m_y - R.m_y, m_z - R.m_z);
}

double Vector3d::Distance  (const Vector3d &V) const
{
	return (double)sqrt(DistanceSquared(V));
}

double Vector3d::DistanceSquared(const Vector3d &V) const
{
	return Subtract(V).LengthSquared();
}

double Vector3d::Length  () const
{
	return (double)sqrt(LengthSquared());
}

double Vector3d::LengthSquared() const
{
	return (m_x * m_x + m_y * m_y + m_z * m_z);
}

const Vector3d & Vector3d::Normalise()
{
	return Normalise(*this);
}

const Vector3d & Vector3d::Normalise( const Vector3d &V )
{
	double r = V.Length();

	if (fabs(r) > V3_EPSILON)				// guard against divide by zero
	{
		return *this = Vector3d(V.m_x / r, V.m_y / r, V.m_z / r);	// normalise and return
	}
	else
	{
		return *this;
	}
}

bool Vector3d::IsZero  (double Tolerance) const
{
	return (LengthSquared() <= Tolerance * Tolerance);
}

bool Vector3d::IsUnit (double Tolerance) const
{
	return fabs(Length() - 1.0) <= Tolerance;
}

bool Vector3d::IsEqual(const Vector3d &V, double Tolerance) const
{
	return Subtract(V).IsZero(Tolerance);
}