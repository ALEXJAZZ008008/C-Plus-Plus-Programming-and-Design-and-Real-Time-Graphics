#include <iostream>
#include <array>
using namespace std;

void main(int argc, char **argv)
{
	cout << "Please enter an RGBA value: ";

	array<int, 4> rgba;
	
	for (int i = 0; i < rgba.size(); i++)
	{
		cin >> rgba[i];
	}

	unsigned int encodedRGBA = rgba[0] | (rgba[1] << 8) | (rgba[2] << 16) | (rgba[3] << 24);

	cout << "Encoded RGBA is: " << encodedRGBA << endl;

	rgba = {(encodedRGBA & 0x000000ff), (encodedRGBA & 0x0000ff00) >> 8, (encodedRGBA & 0x00ff0000) >> 16, (encodedRGBA & 0xff000000) >> 24};

	cout << "Decoded RGBA is: " << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3] << endl;

	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();
}