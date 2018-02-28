#pragma once

#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class Particle
{
public:
	Particle();
	Particle(const XMFLOAT3 &, const XMFLOAT3 &);
	Particle(const Particle &);
	Particle & operator = (const Particle &);
	Particle(const Particle &&);
	Particle & operator = (const Particle &&);
	~Particle();

	const XMFLOAT3 & GetPosition() const
	{
		return m_Position;
	}

	const XMFLOAT3 & GetVelocity() const
	{
		return m_Velocity;
	}

	void SetPosition(const XMFLOAT3 &position)
	{
		m_Position = XMFLOAT3(position.x, position.y, position.z);
	}

	void SetVelocity(const XMFLOAT3 &velocity)
	{
		m_Velocity = XMFLOAT3(velocity.x, velocity.y, velocity.z);
	}

private:
	XMFLOAT3 m_Position, m_Velocity;
};