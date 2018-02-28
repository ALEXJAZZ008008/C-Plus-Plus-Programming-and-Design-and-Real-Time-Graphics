#include "imageVertex.h"

ImageVertex::ImageVertex() : m_Position(), m_Texture()
{
	
}

ImageVertex::ImageVertex(const float pX, const float pY, const float pZ, const float tU, const float tV) : m_Position(XMFLOAT3(pX, pY, pZ)), m_Texture(XMFLOAT2(tU, tV))
{

}

ImageVertex::ImageVertex(const ImageVertex &imageVertex) : m_Position(imageVertex.GetPosition()), m_Texture(imageVertex.GetTexture())
{
	
}

ImageVertex & ImageVertex::operator = (const ImageVertex &imageVertex)
{
	if (this != &imageVertex)
	{
		m_Position = imageVertex.GetPosition();
		m_Texture = imageVertex.GetTexture();
	}

	return *this;
}

ImageVertex::ImageVertex(const ImageVertex &&imageVertex) : m_Position(imageVertex.GetPosition()), m_Texture(imageVertex.GetTexture())
{

}

ImageVertex & ImageVertex::operator = (const ImageVertex &&imageVertex)
{
	if (this != &imageVertex)
	{
		m_Position = imageVertex.GetPosition();
		m_Texture = imageVertex.GetTexture();
	}

	return *this;
}

ImageVertex::~ImageVertex()
{
	try
	{

	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}