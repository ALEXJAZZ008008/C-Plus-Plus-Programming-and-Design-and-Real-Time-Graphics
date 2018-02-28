#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include <fstream>
#include "imageVertex.h"
#include "textureArray.h"

using namespace std;
using namespace DirectX;

class TextLoader
{
public:
	TextLoader();
	TextLoader(ID3D11Device *, ID3D11DeviceContext *, const char * const, const char *);
	TextLoader(const TextLoader &);
	TextLoader & operator = (const TextLoader &);
	TextLoader(const TextLoader &&);
	TextLoader & operator = (const TextLoader &&);
	~TextLoader();

	const XMFLOAT3 * GetText() const
	{
		return m_Text;
	}

	const TextureArray * GetTexture() const
	{
		return m_Texture;
	}

	void SetText(XMFLOAT3 * const text)
	{
		m_Text = text;
	}

	void SetTexture(TextureArray * const texture)
	{
		m_Texture = texture;
	}

	void GetVertices(void * const, const char * const, XMFLOAT2 &) const;

private:
	XMFLOAT3 *m_Text;
	TextureArray *m_Texture;
};