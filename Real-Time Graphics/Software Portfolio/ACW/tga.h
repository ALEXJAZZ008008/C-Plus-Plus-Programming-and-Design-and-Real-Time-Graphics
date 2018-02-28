#pragma once

#include <directxmath.h>
#include <iostream>
#include <array>

using namespace std;
using namespace DirectX;

class TGA
{
public:
	TGA();
	TGA(const TGA &);
	TGA & operator = (const TGA &);
	TGA(const TGA &&);
	TGA & operator = (const TGA &&);
	~TGA();

	const array<char, 12> & GetData1() const
	{
		return m_Data1;
	}
	const short GetWidth() const
	{
		return m_Width;
	}

	const short GetHeight() const
	{
		return m_Height;
	}

	const char GetBPP() const
	{
		return m_BPP;
	}

	const char GetData2() const
	{
		return m_Data2;
	}

	void SetData1(const array<char, 12> & data1)
	{
		m_Data1 = data1;
	}

	void SetWidth(const short width)
	{
		m_Width = width;
	}

	void SetHeight(const short height)
	{
		m_Height = height;
	}

	void SetBPP(const char bpp)
	{
		m_BPP = bpp;
	}

	void SetData2(const char data2)
	{
		m_Data2 = data2;
	}

private:
	array<char, 12> m_Data1;
	short m_Width, m_Height;
	char m_BPP, m_Data2;
};