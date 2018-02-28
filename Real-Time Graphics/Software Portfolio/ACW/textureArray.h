#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include <array>
#include "tga.h"

using namespace std;
using namespace DirectX;

class TextureArray
{
public:
	TextureArray();
	TextureArray(ID3D11Device * const, ID3D11DeviceContext * const, const char * const, const char * const, const char * const);
	TextureArray(const TextureArray &);
	TextureArray & operator = (const TextureArray &);
	TextureArray(const TextureArray &&);
	TextureArray & operator = (const TextureArray &&);
	~TextureArray();

	ID3D11Texture2D * GetTexture() const
	{
		return m_Texture;
	}

	const array<ID3D11ShaderResourceView *, 3> & GetTextureViews() const
	{
		return m_TextureViews;
	}

	const array<char *, 3> & GetTGAs() const
	{
		return m_TGAs;
	}

	void SetTexture(ID3D11Texture2D * const texture)
	{
		m_Texture = texture;
	}

	void SetTextureViews(const array<ID3D11ShaderResourceView *, 3> & textureViews)
	{
		m_TextureViews = textureViews;
	}

	void SetTGAs(const array<char *, 3> & tgas)
	{
		m_TGAs = tgas;
	}

	void LoadTexture(ID3D11Device * const, ID3D11DeviceContext * const, int, const char * const);

private:
	ID3D11Texture2D *m_Texture;
	array<ID3D11ShaderResourceView *, 3> m_TextureViews;
	array<char *, 3> m_TGAs;
};