#include "image.h"

Image::Image() : m_Text1(nullptr), m_Text2(nullptr), m_Text3(nullptr), m_TextLoader(nullptr), m_ImageShader(nullptr), m_Screen(), m_ViewMatrix()
{
	
}

Image::Image(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, const XMFLOAT2 &screen, const XMMATRIX &viewMatrix, const char * const textMap, const char * const textTexture) : m_Text1(new Text(device, 16)), m_Text2(new Text(device, 16)), m_Text3(new Text(device, 16)), m_TextLoader(new TextLoader(device, deviceContext, textMap, textTexture)), m_ImageShader(new ImageShader(device)), m_Screen(screen), m_ViewMatrix(viewMatrix)
{
	m_Text1->Update(deviceContext, m_TextLoader, "NULL", screen, XMFLOAT2(10, 10), XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_Text2->Update(deviceContext, m_TextLoader, "NULL", screen, XMFLOAT2(10, 30), XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_Text3->Update(deviceContext, m_TextLoader, "NULL", screen, XMFLOAT2(10, 50), XMFLOAT3(0.0f, 0.0f, 0.0f));
}

Image::Image(const Image &image) : m_Text1(const_cast<Text *>(image.GetText1())), m_Text2(const_cast<Text *>(image.GetText2())), m_Text3(const_cast<Text *>(image.GetText3())), m_TextLoader(const_cast<TextLoader *>(image.GetTextLoader())), m_ImageShader(const_cast<ImageShader *>(image.GetImageShader())), m_Screen(image.GetScreen()), m_ViewMatrix(image.GetViewMatrix())
{
	
}

Image & Image::operator = (const Image &image)
{
	if (this != &image)
	{
		m_Text1 = const_cast<Text *>(image.GetText1());
		m_Text2 = const_cast<Text *>(image.GetText2());
		m_Text3 = const_cast<Text *>(image.GetText3());
		m_TextLoader = const_cast<TextLoader *>(image.GetTextLoader());
		m_ImageShader = const_cast<ImageShader *>(image.GetImageShader());

		m_Screen = image.GetScreen();

		m_ViewMatrix = image.GetViewMatrix();
	}

	return *this;
}

Image::Image(const Image &&image) : m_Text1(const_cast<Text *>(image.GetText1())), m_Text2(const_cast<Text *>(image.GetText2())), m_Text3(const_cast<Text *>(image.GetText3())), m_TextLoader(const_cast<TextLoader *>(image.GetTextLoader())), m_ImageShader(const_cast<ImageShader *>(image.GetImageShader())), m_Screen(image.GetScreen()), m_ViewMatrix(image.GetViewMatrix())
{

}

Image & Image::operator = (const Image &&image)
{
	if (this != &image)
	{
		m_Text1 = const_cast<Text *>(image.GetText1());
		m_Text2 = const_cast<Text *>(image.GetText2());
		m_Text3 = const_cast<Text *>(image.GetText3());
		m_TextLoader = const_cast<TextLoader *>(image.GetTextLoader());
		m_ImageShader = const_cast<ImageShader *>(image.GetImageShader());

		m_Screen = image.GetScreen();

		m_ViewMatrix = image.GetViewMatrix();
	}

	return *this;
}

Image::~Image()
{
	try
	{
		delete m_Text1;
		delete m_Text2;
		delete m_Text3;

		delete m_TextLoader;
		delete m_ImageShader;
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void Image::Update(ID3D11DeviceContext * const deviceContext, const XMFLOAT2 &screen, const int fps, const int cpu, const float timeScale)
{
	array<char, 5> temporary;

	_itoa_s(fps, temporary.data(), temporary.size(), 10);

	array<char, 12> output;

	strcpy_s(output.data(), output.size(), "FPS: ");
	strcat_s(output.data(), output.size(), temporary.data());

	XMFLOAT3 colour;

	if (fps >= 60)
	{
		colour = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		if (fps <= 30)
		{
			colour = XMFLOAT3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			colour = XMFLOAT3(1.0f, 1.0f, 0.0f);
		}
	}

	m_Text1->Update(deviceContext, m_TextLoader, output.data(), screen, XMFLOAT2(10, 10), colour);

	_itoa_s(cpu, temporary.data(), temporary.size(), 10);

	strcpy_s(output.data(), output.size(), "CPU: ");
	strcat_s(output.data(), output.size(), temporary.data());
	strcat_s(output.data(), output.size(), "%");

	if (cpu <= 33)
	{
		colour = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		if (cpu >= 66)
		{
			colour = XMFLOAT3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			colour = XMFLOAT3(1.0f, 1.0f, 0.0f);
		}
	}

	m_Text2->Update(deviceContext, m_TextLoader, output.data(), screen, XMFLOAT2(10, 30), colour);

	_itoa_s(static_cast<int>(timeScale * 100.0f), temporary.data(), temporary.size(), 10);

	strcpy_s(output.data(), output.size(), "Time: ");
	strcat_s(output.data(), output.size(), temporary.data());

	if (timeScale > 1.0f)
	{
		colour = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		if (timeScale < 1.0f)
		{
			colour = XMFLOAT3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			colour = XMFLOAT3(1.0f, 1.0f, 0.0f);
		}
	}

	m_Text3->Update(deviceContext, m_TextLoader, output.data(), screen, XMFLOAT2(10, 50), colour);
}

void Image::Render(ID3D11DeviceContext * const deviceContext, XMMATRIX &worldMatrix, XMMATRIX &orthographicMatrix)
{
	m_Text1->Render(deviceContext, m_TextLoader, m_ImageShader, worldMatrix, m_ViewMatrix, orthographicMatrix);

	m_Text2->Render(deviceContext, m_TextLoader, m_ImageShader, worldMatrix, m_ViewMatrix, orthographicMatrix);

	m_Text3->Render(deviceContext, m_TextLoader, m_ImageShader, worldMatrix, m_ViewMatrix, orthographicMatrix);
}