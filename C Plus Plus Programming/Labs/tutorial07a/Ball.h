#pragma once

#include "Vector3d.h"
#include "NewtonianObject.h"
#include "Colour.h"

class Ball : public NewtonianObject
{
public:
	Ball(const Vector3d &position, double radius = 1);
	~Ball();

	double GetRadius() const;
	void SetRadius(double radius);

	const Colour &GetColour() const;
	void SetColour(const Colour &colour);

	void ApplyPhysics(double time);
	void ApplyGravity(double time);

private:
	double m_radius;
	Colour m_colour;
};
