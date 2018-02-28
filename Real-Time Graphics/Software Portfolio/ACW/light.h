#pragma once

#include <directxmath.h>
#include <iostream>
#include <array>

using namespace std;
using namespace DirectX;

class Light
{
public:
	Light();
	Light(const Light &);
	Light & operator = (const Light &);
	Light(const Light &&);
	Light & operator = (const Light &&);
	~Light();

	const XMFLOAT4 & GetPosition() const
	{
		return m_Position;
	}

	const XMFLOAT4 & GetAmbientColour() const
	{
		return m_AmbientColour;
	}

	const XMFLOAT4 & GetDiffuseColour() const
	{
		return m_DiffuseColour;
	}

	const XMFLOAT4 & GetSpecularColour() const
	{
		return m_SpecularColour;
	}

	const int GetCount() const
	{
		return m_Count;
	}

	const float GetVelocity() const
	{
		return m_Velocity;
	}

	const array<XMFLOAT3 *, 3> & GetPath() const
	{
		return m_Path;
	}

	void SetPosition(const XMFLOAT4 &position)
	{
		m_Position = position;
	}

	void SetAmbientColour(const XMFLOAT4 &ambientColour)
	{
		m_AmbientColour = ambientColour;
	}

	void SetDiffuseColour(const XMFLOAT4 &diffuseColour)
	{
		m_DiffuseColour = diffuseColour;
	}

	void SetSpecularColour(const XMFLOAT4 &specularColour)
	{
		m_SpecularColour = specularColour;
	}

	void SetPosition(const float x, const float y, const float z, const float w)
	{
		m_Position = XMFLOAT4(x, y, z, w);
	}

	void SetAmbientColour(const float red, const float green, const float blue, const float alpha)
	{
		m_AmbientColour = XMFLOAT4(red, green, blue, alpha);
	}

	void SetDiffuseColour(const float red, const float green, const float blue, const float alpha)
	{
		m_DiffuseColour = XMFLOAT4(red, green, blue, alpha);
	}

	void SetSpecularColour(const float red, const float green, const float blue, const float alpha)
	{
		m_SpecularColour = XMFLOAT4(red, green, blue, alpha);
	}

	void SetCount(const int count)
	{
		m_Count = count;
	}

	void SetVelocity(const float velocity)
	{
		m_Velocity = velocity;
	}

	void SetPath(const array<XMFLOAT3 *, 3> & path)
	{
		m_Path = path;
	}

	void SetPathAt(const XMFLOAT3 &path, const int at)
	{
		m_Path.at(at)->x = path.x;
		m_Path.at(at)->y = path.y;
		m_Path.at(at)->z = path.z;
	}

	void Update(const float);

private:
	XMFLOAT4 m_Position, m_AmbientColour, m_DiffuseColour, m_SpecularColour;
	int m_Count;
	float m_Velocity;
	array<XMFLOAT3 *, 3> m_Path;
};