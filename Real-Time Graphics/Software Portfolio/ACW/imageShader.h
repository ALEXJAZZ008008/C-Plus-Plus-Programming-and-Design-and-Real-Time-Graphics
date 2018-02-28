#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;
using namespace DirectX;

class ImageShader
{
private:
	struct MatrixBuffer
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Projection;
	};

	struct ImageBuffer
	{
		XMFLOAT4 Colour;
	};

public:
	ImageShader();
	explicit ImageShader(ID3D11Device * const);
	ImageShader(const ImageShader &);
	ImageShader & operator = (const ImageShader &);
	ImageShader(const ImageShader &&);
	ImageShader & operator = (const ImageShader &&);
	~ImageShader();

	ID3D11VertexShader * GetVertexShader() const
	{
		return m_VertexShader;
	}

	ID3D11PixelShader * GetPixelShader() const
	{
		return m_PixelShader;
	}

	ID3D11InputLayout * GetLayout() const
	{
		return m_Layout;
	}

	ID3D11Buffer * GetMatrixBuffer() const
	{
		return m_MatrixBuffer;
	}

	ID3D11Buffer * GetImageBuffer() const
	{
		return m_ImageBuffer;
	}

	ID3D11SamplerState * GetSampleState() const
	{
		return m_SampleState;
	}

	void SetVertexShader(ID3D11VertexShader * const vertexShader)
	{
		m_VertexShader = vertexShader;
	}

	void SetPixelShader(ID3D11PixelShader * const pixelShader)
	{
		m_PixelShader = pixelShader;
	}

	void SetLayout(ID3D11InputLayout * const layout)
	{
		m_Layout = layout;
	}

	void SetMatrixBuffer(ID3D11Buffer * const matrixBuffer)
	{
		m_MatrixBuffer = matrixBuffer;
	}

	void SetImageBuffer(ID3D11Buffer * const imageBuffer)
	{
		m_ImageBuffer = imageBuffer;
	}

	void SetSampleState(ID3D11SamplerState * const sampleState)
	{
		m_SampleState = sampleState;
	}

	bool Render(ID3D11DeviceContext * const, const int, XMMATRIX &, XMMATRIX &, XMMATRIX &, ID3D11ShaderResourceView * const, const XMFLOAT4 &) const;

private:
	ID3D11VertexShader *m_VertexShader;
	ID3D11PixelShader *m_PixelShader;
	ID3D11InputLayout *m_Layout;
	ID3D11Buffer *m_MatrixBuffer;
	ID3D11Buffer *m_ImageBuffer;
	ID3D11SamplerState *m_SampleState;
};