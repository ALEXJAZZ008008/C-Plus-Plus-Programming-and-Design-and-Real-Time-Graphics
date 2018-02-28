#pragma once

#include "Vector3d.h"

class NewtonianObject
{
public:
	NewtonianObject();
	~NewtonianObject();

	virtual void ApplyPhysics(double time)
	{

	};

protected:
	double gravity;
	Vector3d *m_position, *m_velocity;
};