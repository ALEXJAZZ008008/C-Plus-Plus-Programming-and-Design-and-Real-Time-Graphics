#include <iostream>
using namespace std;

#include "vector3d.h"

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main (int, char**)
{
	Vector3d a(1,2,3);
	Vector3d b(2,2,3);
	Vector3d c;

	c = a.Add(b);

	cout << "cx= " << c.x << endl;
	cout << "cy= " << c.y << endl;
	cout << "cz= " << c.z << endl;

	return CloseProgram();
}