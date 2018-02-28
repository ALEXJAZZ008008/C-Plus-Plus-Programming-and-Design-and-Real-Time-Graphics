#include <iostream>
#include <cmath>
using namespace std;

/*
* Calculates the area of a rectangle, then calculates the sum of the areas of two rectangles.
*/

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

const double CalculateArea(double length, double height)
{
	return length * height;
}

int main(int argc, char** argv)
{
	double lengthA = 2.0, heightA = 3.0, lengthB = 4.0, heightB = 5.0;

	// Calculate the area of A
	double areaA = CalculateArea(lengthA, heightA);

	cout << "Area of A = " << areaA << endl;

	// Calculate the area of B
	double areaB = CalculateArea(lengthB, heightB);

	cout << "Area of B = " << areaB << endl;

	// Calculate and sum the areas of A and B
	cout << "Area of A + Area of B = " << areaA + areaB << endl;

	return CloseProgram();
}