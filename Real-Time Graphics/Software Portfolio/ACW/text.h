#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include "imageVertex.h"
#include "textLoader.h"
#include "imageShader.h"

using namespace std;
using namespace DirectX;

class Text
{
public:
	Text();
	Text(ID3D11Device * const, const int);
	Text(const Text &);
	Text & operator = (const Text &);
	Text(const Text &&);
	Text & operator = (const Text &&);
	~Text();

	ID3D11Buffer * GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}

	ID3D11Buffer * GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	const int GetCount() const
	{
		return m_Count;
	}

	const int GetMaximumCount() const
	{
		return m_MaximumCount;
	}

	const XMFLOAT3 & GetColour() const
	{
		return m_Colour;
	}

	void SetVertexBuffer(ID3D11Buffer * const vertexBuffer)
	{
		m_VertexBuffer = vertexBuffer;
	}

	void SetIndexBuffer(ID3D11Buffer * const indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}

	void SetCount(const int count)
	{
		m_Count = count;
	}

	void SetMaximumCount(const int maximumCount)
	{
		m_MaximumCount = maximumCount;
	}

	void SetColour(const XMFLOAT3 &colour)
	{
		m_Colour = colour;
	}

	void Update(ID3D11DeviceContext * const, const TextLoader * const, const char * const, const XMFLOAT2 &, const XMFLOAT2 &, const XMFLOAT3 &);
	void Render(ID3D11DeviceContext * const, const TextLoader * const, const ImageShader * const, XMMATRIX &, XMMATRIX &, XMMATRIX &) const;

private:
	ID3D11Buffer *m_VertexBuffer;
	ID3D11Buffer *m_IndexBuffer;
	int m_Count, m_MaximumCount;
	XMFLOAT3 m_Colour;
};