#include "tga.h"

TGA::TGA() : m_Data1(), m_Width(0), m_Height(0), m_BPP(' '), m_Data2(' ')
{

}

TGA::TGA(const TGA &tga) : m_Data1(tga.GetData1()), m_Width(tga.GetWidth()), m_Height(tga.GetHeight()), m_BPP(tga.GetBPP()), m_Data2(tga.GetData2())
{

}

TGA & TGA::operator = (const TGA &tga)
{
	if (this != &tga)
	{
		m_Data1 = tga.GetData1();
		m_Width = tga.GetWidth();
		m_Height = tga.GetHeight();
		m_BPP = tga.GetBPP();
		m_Data2 = tga.GetData2();
	}

	return *this;
}

TGA::TGA(const TGA &&tga) : m_Data1(tga.GetData1()), m_Width(tga.GetWidth()), m_Height(tga.GetHeight()), m_BPP(tga.GetBPP()), m_Data2(tga.GetData2())
{

}

TGA & TGA::operator = (const TGA &&tga)
{
	if (this != &tga)
	{
		m_Data1 = tga.GetData1();
		m_Width = tga.GetWidth();
		m_Height = tga.GetHeight();
		m_BPP = tga.GetBPP();
		m_Data2 = tga.GetData2();
	}

	return *this;
}

TGA::~TGA()
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