#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include <vector>
#include <random>
#include "particle.h"
#include "particleVertex.h"
#include "particlesShader.h"
#include "textureArray.h"

using namespace std;
using namespace DirectX;

class Particles
{
public:
	Particles();
	Particles(ID3D11Device *, ID3D11DeviceContext *, const char *);
	Particles(const Particles &);
	Particles & operator = (const Particles &);
	Particles(const Particles &&);
	Particles & operator = (const Particles &&);
	~Particles();

	const vector<Particle> & GetParticles() const
	{
		return m_Particles;
	}

	const ParticlesShader * GetParticlesShader() const
	{
		return m_ParticlesShader;
	}

	const ParticleVertex * GetParticlesVertices() const
	{
		return m_ParticlesVertices;
	}

	const TextureArray * GetTextureArray() const
	{
		return m_TextureArray;
	}

	const ID3D11Buffer * GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}

	const ID3D11Buffer * GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	const float GetRotation() const
	{
		return m_Rotation;
	}

	const float GetAcceleration() const
	{
		return m_Acceleration;
	}

	const float GetVelocity() const
	{
		return m_Velocity;
	}

	const float GetVelocityVariation() const
	{
		return m_VelocityVariation;
	}

	const float GetSize() const
	{
		return m_Size;
	}

	const float GetSpawnRate() const
	{
		return m_SpawnRate;
	}

	const float GetTime() const
	{
		return m_Time;
	}

	const int GetCount() const
	{
		return m_Count;
	}

	const int GetMaxNumberOfParticles() const
	{
		return m_MaxNumberOfParticles;
	}

	void SetParticles(const vector<Particle> &particles)
	{
		m_Particles = particles;
	}

	void SetParticlesShader(ParticlesShader * const particlesShader)
	{
		m_ParticlesShader = particlesShader;
	}

	void SetParticlesVertices(ParticleVertex * const particleVertex)
	{
		m_ParticlesVertices = particleVertex;
	}

	void SetTextureArray(TextureArray * const textureArray)
	{
		m_TextureArray = textureArray;
	}

	void SetVertexBuffer(ID3D11Buffer * const vertexBuffer)
	{
		m_VertexBuffer = vertexBuffer;
	}

	void SetIndexBuffer(ID3D11Buffer * const indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}

	void SetRotation(const float rotation)
	{
		m_Rotation = rotation;
	}

	void SetAcceleration(const float acceleration)
	{
		m_Acceleration = acceleration;
	}

	void SetVelocity(const float velocity)
	{
		m_Velocity = velocity;
	}

	void SetVelocityVariation(const float velocityVariation)
	{
		m_VelocityVariation = velocityVariation;
	}

	void SetSize(const float size)
	{
		m_Size = size;
	}

	void SetSpawnRate(const float spawnRate)
	{
		m_SpawnRate = spawnRate;
	}

	void SetTime(const float time)
	{
		m_Time = time;
	}

	void SetCount(const int count)
	{
		m_Count = count;
	}

	void SetMaxNumberOfParticles(const int maxNumberOfParticles)
	{
		m_MaxNumberOfParticles = maxNumberOfParticles;
	}

	void Update(ID3D11DeviceContext *, const XMFLOAT3 &, const XMFLOAT3 &, const bool, const float);
	void Render(ID3D11DeviceContext * const, const XMMATRIX &, XMMATRIX &, XMMATRIX &, const float) const;

private:
	vector<Particle> m_Particles;
	ParticlesShader *m_ParticlesShader;
	ParticleVertex *m_ParticlesVertices;
	TextureArray *m_TextureArray;
	ID3D11Buffer *m_VertexBuffer;
	ID3D11Buffer *m_IndexBuffer;
	float m_Rotation, m_Acceleration, m_Velocity, m_VelocityVariation, m_Size, m_SpawnRate, m_Time;
	int m_Count, m_MaxNumberOfParticles;
};