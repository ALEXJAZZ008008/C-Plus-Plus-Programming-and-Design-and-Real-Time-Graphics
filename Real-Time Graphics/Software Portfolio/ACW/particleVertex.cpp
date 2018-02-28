#include "particleVertex.h"

ParticleVertex::ParticleVertex() : m_Position(), m_Texture()
{

}

ParticleVertex::ParticleVertex(const ParticleVertex &particleVertex) : m_Position(particleVertex.GetPosition()), m_Texture(particleVertex.GetTexture())
{
	
}

ParticleVertex & ParticleVertex::operator = (const ParticleVertex &particleVertex)
{
	if (this != &particleVertex)
	{
		m_Position = particleVertex.GetPosition();
		m_Texture = particleVertex.GetTexture();
	}

	return *this;
}

ParticleVertex::ParticleVertex(const ParticleVertex &&particleVertex) : m_Position(particleVertex.GetPosition()), m_Texture(particleVertex.GetTexture())
{

}

ParticleVertex & ParticleVertex::operator = (const ParticleVertex &&particleVertex)
{
	if (this != &particleVertex)
	{
		m_Position = particleVertex.GetPosition();
		m_Texture = particleVertex.GetTexture();
	}

	return *this;
}

ParticleVertex::~ParticleVertex()
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