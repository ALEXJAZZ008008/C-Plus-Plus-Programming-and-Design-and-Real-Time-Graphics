#pragma once

#include "Vector3d.h"
#include "NewtonianObject.h"
#include "Colour.h"

class Cube : public NewtonianObject
{
public:
	Cube(const Vector3d &position, double size = 1);
	~Cube();

	double GetSize() const;
	void SetSize(double size);

	const Colour &GetColour() const;
	void SetColour(const Colour &colour);

	void ApplyPhysics(double time);

private:
	double m_size;
	Colour m_colour;
};
