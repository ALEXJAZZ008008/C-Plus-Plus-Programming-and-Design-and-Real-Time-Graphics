#include "light.h"

Light::Light() : m_Position(), m_AmbientColour(), m_DiffuseColour(), m_SpecularColour(), m_Count(0), m_Velocity(0.5f), m_Path()
{
	for (int i = 0; i < m_Path.size(); i++)
	{
		m_Path.at(i) = new XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
}

Light::Light(const Light &light) : m_Position(light.GetPosition()), m_AmbientColour(light.GetAmbientColour()), m_DiffuseColour(light.GetDiffuseColour()), m_SpecularColour(light.GetSpecularColour()), m_Count(light.GetCount()), m_Velocity(light.GetVelocity()), m_Path(light.GetPath())
{
	
}

Light & Light::operator = (const Light &light)
{
	if (this != &light)
	{
		m_Position = light.GetPosition();
		m_AmbientColour = light.GetAmbientColour();
		m_DiffuseColour = light.GetDiffuseColour();
		m_SpecularColour = light.GetSpecularColour();
		m_Count = light.GetCount();
		m_Velocity = light.GetVelocity();
		m_Path = light.GetPath();
	}

	return *this;
}

Light::Light(const Light &&light) : m_Position(light.GetPosition()), m_AmbientColour(light.GetAmbientColour()), m_DiffuseColour(light.GetDiffuseColour()), m_SpecularColour(light.GetSpecularColour()), m_Count(light.GetCount()), m_Velocity(light.GetVelocity()), m_Path(light.GetPath())
{

}

Light & Light::operator = (const Light &&light)
{
	if (this != &light)
	{
		m_Position = light.GetPosition();
		m_AmbientColour = light.GetAmbientColour();
		m_DiffuseColour = light.GetDiffuseColour();
		m_SpecularColour = light.GetSpecularColour();
		m_Count = light.GetCount();
		m_Velocity = light.GetVelocity();
		m_Path = light.GetPath();
	}

	return *this;
}

Light::~Light()
{
	try
	{
		for (int i = 0; i < m_Path.size(); i++)
		{
			delete m_Path.at(i);
		}
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void Light::Update(const float dt)
{
	if (sqrt(pow(m_Position.x - m_Path.at(m_Count)->x, 2) + pow(m_Position.y - m_Path.at(m_Count)->y, 2) + pow(m_Position.z - m_Path.at(m_Count)->z, 2)) > 0.005)
	{
		const XMFLOAT3 direction = XMFLOAT3(m_Path.at(m_Count)->x - m_Position.x, m_Path.at(m_Count)->y - m_Position.y, m_Path.at(m_Count)->z - m_Position.z);

		const float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));

		const XMFLOAT3 velocity = XMFLOAT3((direction.x / magnitude) * m_Velocity, (direction.y / magnitude) * m_Velocity, (direction.z / magnitude) * m_Velocity);

		m_Position = XMFLOAT4(m_Position.x + (velocity.x * dt), m_Position.y + (velocity.y * dt), m_Position.z + (velocity.z * dt), m_Position.w);
	}
	else
	{
		if (m_Count < 2)
		{
			m_Count++;
		}
		else
		{
			m_Count = 0;
		}
	}
}