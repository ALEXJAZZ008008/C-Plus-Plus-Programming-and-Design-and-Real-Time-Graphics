#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include "imageVertex.h"

using namespace std;
using namespace DirectX;

class ModelVertex
{
public:
	ModelVertex();
	ModelVertex(const float, const float, const float, const float, const float, const float, const float, const float);
	ModelVertex(const float, const float, const float, const float, const float, const float, const float, const float, const float, const float, const float, const float, const float, const float);
	ModelVertex(const ModelVertex &);
	ModelVertex & operator = (const ModelVertex &);
	ModelVertex(const ModelVertex &&);
	ModelVertex & operator = (const ModelVertex &&);
	~ModelVertex();

	const ImageVertex & GetImageVertex() const
	{
		return m_ImageVertex;
	}

	const XMFLOAT3 & GetPosition() const
	{
		return m_ImageVertex.GetPosition();
	}

	const XMFLOAT2 & GetTexture() const
	{
		return m_ImageVertex.GetTexture();
	}

	const XMFLOAT3 & GetNormal() const
	{
		return m_Normal;
	}

	const XMFLOAT3 & GetTangent() const
	{
		return m_Tangent;
	}

	const XMFLOAT3 & GetBinormal() const
	{
		return m_Binormal;
	}

	void SetImageVertex(const ImageVertex &imageVertex)
	{
		m_ImageVertex = imageVertex;
	}

	void SetPosition(const XMFLOAT3 &position)
	{
		m_ImageVertex.SetPosition(position);
	}

	void SetTexture(const XMFLOAT2 &texture)
	{
		m_ImageVertex.SetTexture(texture);
	}

	void SetNormal(const XMFLOAT3 &normal)
	{
		m_Normal = normal;
	}

	void SetTangent(const XMFLOAT3 &tangent)
	{
		m_Tangent = tangent;
	}

	void SetBinormal(const XMFLOAT3 &binormal)
	{
		m_Binormal = binormal;
	}

	void SetPosition(const float x, const float y, const float z)
	{
		m_ImageVertex.SetPosition(XMFLOAT3(x, y, z));
	}

	void SetTexture(const float u, const float v)
	{
		m_ImageVertex.SetTexture(XMFLOAT2(u, v));
	}

	void SetNormal(const float x, const float y, const float z)
	{
		m_Normal = XMFLOAT3(x, y, z);
	}

	void SetTangent(const float x, const float y, const float z)
	{
		m_Tangent = XMFLOAT3(x, y, z);
	}

	void SetBinormal(const float x, const float y, const float z)
	{
		m_Binormal = XMFLOAT3(x, y, z);
	}

private:
	ImageVertex m_ImageVertex;
	XMFLOAT3 m_Normal;
	XMFLOAT3 m_Tangent;
	XMFLOAT3 m_Binormal;
};