#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include <array>
#include "imageVertex.h"
#include "text.h"
#include "textLoader.h"
#include "imageShader.h"

using namespace std;
using namespace DirectX;

class Image
{
public:
	Image();
	Image(ID3D11Device *, ID3D11DeviceContext *, const XMFLOAT2 &, const XMMATRIX &, const char *, const char *);
	Image(const Image &);
	Image & operator = (const Image &);
	Image(const Image &&);
	Image & operator = (const Image &&);
	~Image();

	const Text * GetText1() const
	{
		return m_Text1;
	}

	const Text * GetText2() const
	{
		return m_Text2;
	}

	const Text * GetText3() const
	{
		return m_Text3;
	}

	const TextLoader * GetTextLoader() const
	{
		return m_TextLoader;
	}

	const ImageShader * GetImageShader() const
	{
		return m_ImageShader;
	}

	const XMFLOAT2 & GetScreen() const
	{
		return m_Screen;
	}

	const XMMATRIX & GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	void SetText1(Text * const text1)
	{
		m_Text1 = text1;
	}

	void SetText2(Text * const text2)
	{
		m_Text2 = text2;
	}

	void SetText3(Text * const text3)
	{
		m_Text3 = text3;
	}

	void SetTextLoader(TextLoader * const textLoader)
	{
		m_TextLoader = textLoader;
	}

	void SetImageShader(ImageShader * const imageShader)
	{
		m_ImageShader = imageShader;
	}

	void SetScreen(const XMFLOAT2 &screen)
	{
		m_Screen = screen;
	}

	void SetViewMatrix(const XMMATRIX &viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
	}

	void Update(ID3D11DeviceContext * const, const XMFLOAT2 &, const int, const int, const float);
	void Render(ID3D11DeviceContext * const, XMMATRIX &, XMMATRIX &);

private:
	Text *m_Text1;
	Text *m_Text2;
	Text *m_Text3;
	TextLoader *m_TextLoader;
	ImageShader *m_ImageShader;
	XMFLOAT2 m_Screen;
	XMMATRIX m_ViewMatrix;
};