#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <iostream>
#include <fstream>
#include <array>
#include "light.h"

using namespace std;
using namespace DirectX;

class ShadowShader
{
private:
	struct MatrixBuffer
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Projection;
	};

	struct ObjectBuffer
	{
		float ObjectType;
		float ObjectState;
		float RenderState;
		float TimeElapsed;
		float TimeOffset;
		XMFLOAT3 ObjectBufferPabbing;
	};

	struct LightBuffer
	{
		XMFLOAT4 AmbientColour[3];
	};

	struct BlendBuffer
	{
		float BlendAmount;
		XMFLOAT3 BlendBufferPadding;
	};

public:
	ShadowShader();
	explicit ShadowShader(ID3D11Device * const);
	ShadowShader(const ShadowShader &);
	ShadowShader & operator = (const ShadowShader &);
	ShadowShader(const ShadowShader &&);
	ShadowShader & operator = (const ShadowShader &&);
	~ShadowShader();

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

	ID3D11Buffer * GetObjectBuffer() const
	{
		return m_ObjectBuffer;
	}

	ID3D11Buffer * GetLightBuffer() const
	{
		return m_LightBuffer;
	}

	ID3D11Buffer * GetBlendBuffer() const
	{
		return m_BlendBuffer;
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

	void SetObjectBuffer(ID3D11Buffer * const objectBuffer)
	{
		m_ObjectBuffer = objectBuffer;
	}

	void SetLightBuffer(ID3D11Buffer * const lightBuffer)
	{
		m_LightBuffer = lightBuffer;
	}

	void SetBlendBuffer(ID3D11Buffer * const blendBuffer)
	{
		m_BlendBuffer = blendBuffer;
	}

	void SetSampleState(ID3D11SamplerState * const sampleState)
	{
		m_SampleState = sampleState;
	}

	bool Render(ID3D11DeviceContext * const, const int, const XMMATRIX &, const XMMATRIX &, const XMMATRIX &, const Light * const, const float, const float, const float, const float, const float, const float) const;

private:
	ID3D11VertexShader *m_VertexShader;
	ID3D11PixelShader *m_PixelShader;
	ID3D11InputLayout *m_Layout;
	ID3D11Buffer *m_MatrixBuffer;
	ID3D11Buffer *m_ObjectBuffer;
	ID3D11Buffer *m_LightBuffer;
	ID3D11Buffer *m_BlendBuffer;
	ID3D11SamplerState *m_SampleState;
};