#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class ParticleVertex
{
public:
	ParticleVertex();
	ParticleVertex(const ParticleVertex &);
	ParticleVertex & operator = (const ParticleVertex &);
	ParticleVertex(const ParticleVertex &&);
	ParticleVertex & operator = (const ParticleVertex &&);
	~ParticleVertex();

	const XMFLOAT3 & GetPosition() const
	{
		return m_Position;
	}

	const XMFLOAT2 & GetTexture() const
	{
		return m_Texture;
	}

	void SetPosition(const XMFLOAT3 &position)
	{
		m_Position = position;
	}

	void SetTexture(const XMFLOAT2 &texture)
	{
		m_Texture = texture;
	}

	void SetPosition(const float x, const float y, const float z)
	{
		m_Position = XMFLOAT3(x, y, z);
	}

	void SetTexture(const float u, const float v)
	{
		m_Texture = XMFLOAT2(u, v);
	}

private:
	XMFLOAT3 m_Position;
	XMFLOAT2 m_Texture;
};