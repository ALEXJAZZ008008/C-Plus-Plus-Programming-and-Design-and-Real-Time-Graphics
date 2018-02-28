#include <crtdbg.h>

#include "cube.h"

#ifdef _DEBUG
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

Cube::Cube(const Vector3d &position, double size)
{
	m_position = new Vector3d(position.GetX(), position.GetY(), position.GetZ());
	m_velocity = new Vector3d();
	SetSize(size);
}

Cube::~Cube()
{
	if (m_position)
	{
		delete m_position;
	}

	if (m_velocity)
	{
		delete m_velocity;
	}
}

double Cube::GetSize() const
{
	return m_size;
}

void Cube::SetSize(double size)
{
	if (size > 0)
	{
		m_size = size;
	}
}

const Colour &Cube::GetColour() const
{
	return m_colour;
}

void Cube::SetColour(const Colour &colour)
{
	m_colour = colour;
}

void Cube::ApplyPhysics(double time)
{
	
}