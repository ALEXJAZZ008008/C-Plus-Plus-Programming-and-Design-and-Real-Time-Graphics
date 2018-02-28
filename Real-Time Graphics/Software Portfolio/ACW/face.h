#pragma once

#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class Face
{
public:
	Face();
	Face(const Face &);
	Face & operator = (const Face &);
	Face(const Face &&);
	Face & operator = (const Face &&);
	~Face();

	const XMFLOAT3 & GetVectorIndex() const
	{
		return m_VectorIndex;
	}

	const XMFLOAT3 & GetTextureIndex() const
	{
		return m_TextureIndex;
	}

	const XMFLOAT3 & GetNormalIndex() const
	{
		return m_NormalIndex;
	}

	void SetVectorIndex(const XMFLOAT3 &vectorIndex)
	{
		m_VectorIndex = vectorIndex;
	}

	void SetTextureIndex(const XMFLOAT3 &textureIndex)
	{
		m_TextureIndex = textureIndex;
	}

	void SetNormalIndex(const XMFLOAT3 &normalIndex)
	{
		m_NormalIndex = normalIndex;
	}

	void SetVectorIndex(const float x, const float y, const float z)
	{
		m_VectorIndex = XMFLOAT3(x, y, z);
	}

	void SetTextureIndex(const float x, const float y, const float z)
	{
		m_TextureIndex = XMFLOAT3(x, y, z);
	}

	void SetNormalIndex(const float x, const float y, const float z)
	{
		m_NormalIndex = XMFLOAT3(x, y, z);
	}

private:
	XMFLOAT3 m_VectorIndex, m_TextureIndex, m_NormalIndex;
};