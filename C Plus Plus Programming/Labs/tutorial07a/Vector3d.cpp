#include "vector3d.h"

Vector3d::Vector3d(double x, double y, double z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

Vector3d::~Vector3d(void)
{

}

double Vector3d::GetX() const
{
	return m_x;
}

void Vector3d::SetX(double x)
{
	m_x = x;
}

double Vector3d::GetY() const
{
	return m_y;
}

void Vector3d::SetY(double y)
{
	m_y = y;
}

double Vector3d::GetZ() const
{
	return m_z;
}

void Vector3d::SetZ(double z)
{
	m_z = z;
}
