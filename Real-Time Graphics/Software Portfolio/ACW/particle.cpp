#include "particle.h"

Particle::Particle() : m_Position(), m_Velocity()
{
	
}

Particle::Particle(const XMFLOAT3 &position, const XMFLOAT3 &velocity) : m_Position(XMFLOAT3(position.x, position.y, position.z)), m_Velocity(XMFLOAT3(velocity.x, velocity.y, velocity.z))
{

}

Particle::Particle(const Particle &particle) : m_Position(particle.GetPosition()), m_Velocity(particle.GetVelocity())
{
	
}

Particle & Particle::operator = (const Particle &particle)
{
	if (this != &particle)
	{
		m_Position = particle.GetPosition();
		m_Velocity = particle.GetVelocity();
	}

	return *this;
}

Particle::Particle(const Particle &&particle) : m_Position(particle.GetPosition()), m_Velocity(particle.GetVelocity())
{

}

Particle & Particle::operator = (const Particle &&particle)
{
	if (this != &particle)
	{
		m_Position = particle.GetPosition();
		m_Velocity = particle.GetVelocity();
	}

	return *this;
}

Particle::~Particle()
{
	try
	{

	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}