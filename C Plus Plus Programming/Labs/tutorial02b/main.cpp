#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
using namespace std;

/*
* Calculates the roots for a quadratic equation
* No account is taken of an imaginary root or floating point overflows
*/

//TODO: Improve the efficiency of the program
//TODO: Output the roots to only 3 decimal places

void main (int argc, char **argv)
{
	cout << "Enter the coefficiants for a quadratic equation: ";

	double a, b, c;
	cin >> a >> b >> c;

	double denominator = (2.0f * a);

	if (denominator == 0)
	{
		cout << "The denominator is zero" << endl;
	}
	else
	{
		double negativeB = 0 - b;
		double numerator = sqrt((b * b) - (4.0f * a * c));

		complex<double> root1 = (negativeB + numerator) / denominator;
		complex<double> root2 = (negativeB - numerator) / denominator;

		cout << fixed << setprecision(3);

		if (root1 == root2)
		{
			cout << "The root of the equation " << a << "x^2 + " << b << "x + " << c << " is " << root1;
		}
		else
		{
			cout << "The roots of the equation " << a << "x^2 + " << b << "x + " << c << " are " << root1 << " and " << root2;
		}
	}

	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();
}
