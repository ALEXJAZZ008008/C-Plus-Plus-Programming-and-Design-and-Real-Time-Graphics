#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
* Calculates the roots for a quadratic equation
* No account is taken of an imaginary root or floating point overflows
*/

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

void CalculateRoots(double a, double b, double c)
{
	double operand = b * b - 4.0 * a * c;
	double root1 = (-b + sqrt(operand)) / (2.0 * a);
	double root2 = (-b - sqrt(operand)) / (2.0 * a);

	cout << "The roots of the equation " << a << "x^2 + " << b << "x + " << c << "\n" << "are " << root1 << " and " << root2 << endl;
}

int main (int argc, char **argv)
{
	cout << "Enter the coefficiants for a quadratic equation: ";

	double a, b, c;
	cin >> a >> b >> c;

	CalculateRoots(a, b, c);

	return CloseProgram();
}
