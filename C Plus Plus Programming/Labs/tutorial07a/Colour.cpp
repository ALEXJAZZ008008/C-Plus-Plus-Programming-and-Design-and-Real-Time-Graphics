#include "colour.h"

Colour::Colour(unsigned char red, unsigned char green, unsigned char blue)
{
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

Colour::~Colour()
{

}

unsigned char Colour::GetRed() const
{
	return m_red;
}

unsigned char Colour::GetGreen() const
{
	return m_green;
}

unsigned char Colour::GetBlue() const
{
	return m_blue;
}
 