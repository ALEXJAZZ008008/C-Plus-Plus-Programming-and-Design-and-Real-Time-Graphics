#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class ImageVertex
{
public:
	ImageVertex();
	ImageVertex(const float, const float, const float, const float, const float);
	ImageVertex(const ImageVertex &);
	ImageVertex & operator = (const ImageVertex &);
	ImageVertex(const ImageVertex &&);
	ImageVertex & operator = (const ImageVertex &&);
	~ImageVertex();

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