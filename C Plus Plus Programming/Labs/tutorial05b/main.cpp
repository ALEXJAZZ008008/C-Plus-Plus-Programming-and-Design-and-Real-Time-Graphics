#include <windows.h>
using namespace std;

#include "matrix33d.h"

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main (int, char**)
{
	double matrix[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	Matrix33d a(matrix);
	Matrix33d b;

	cin >> b;

	Matrix33d c = a * b;

	cout << c;

	cout << -c;

	return CloseProgram();
}
