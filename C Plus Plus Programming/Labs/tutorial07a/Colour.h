#pragma once

class Colour
{
public:
	Colour(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);
	~Colour();

	unsigned char GetRed() const;
	unsigned char GetGreen() const;
	unsigned char GetBlue() const;

private:
	unsigned char m_red, m_green, m_blue;
};
 