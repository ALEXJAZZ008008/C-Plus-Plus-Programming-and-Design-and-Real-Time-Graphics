#include <crtdbg.h>

#include "ball.h"

#ifdef _DEBUG
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

Ball::Ball(const Vector3d &position, double radius)
{
	m_position = new Vector3d(position.GetX(), position.GetY(), position.GetZ());
	m_velocity = new Vector3d();
	SetRadius(radius);
}

Ball::~Ball()
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

double Ball::GetRadius() const
{
	return m_radius;
}

void Ball::SetRadius(double radius)
{
	if (radius > 0)
	{
		m_radius = radius;
	}
}

const Colour &Ball::GetColour() const
{
	return m_colour;
}

void Ball::SetColour(const Colour &colour)
{
	m_colour = colour;
}

void Ball::ApplyPhysics(double time)
{
	ApplyGravity(time);
}

void Ball::ApplyGravity(double time)
{
	// Do gravity
	m_velocity->SetY(m_velocity->GetY() + (gravity * time));
	m_position->SetY(m_position->GetY() + ((m_velocity->GetY() * time) + (0.5 * (gravity * (time * time)))));
}