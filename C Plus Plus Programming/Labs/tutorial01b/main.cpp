#include <iostream>
using namespace std;

void functionA(int i)
{
	switch (i)
	{
		case 1 :

			cout << "I is 1" << endl;

			break;

		case 2 :

			cout << "I is in the middle" << endl;

			break;

		case 3 :

			cout << "I is in the middle" << endl;

			break;

		case 4 :

			cout << "I is in the middle" << endl;

			break;

		default :

			cout << "I is outside of range" << endl;

			break;
	}
}

void functionB(int i)
{
	if (i == 1)
	{ 
		cout << "I is 1" << endl;
	}
	else
	{
		if (i >= 5)
		{
			cout << "I is outside of range" << endl;
		}
		else
		{
			cout << "I is in the middle" << endl;
		}
	}
}

int functionC(int i)
{
	return (i < 5) ? i : 5;
}

bool functionD(int i)
{
	return i;
}

void functionE(int &i, int &j)
{
	if (j != 0)
	{
		if ((i / j) == 4)
		{
			i = 100;
		}
	}

	if ((i * j) == 8)
	{
		i = 50;
	}
	else
	{
		j = 60;
	}

	if (i < j)
	{
		j *= 2;
	}
	else
	{
		if (i % 2 == 0)
		{
			i *= 2;
		}
		else
		{
			i++;
			j++;
		}
	}

	if (i == 0)
	{
		if (j == 0)
		{
			i = 1;
			j = 2;
		}
		else
		{
			i = 5;
			j = 10;
		}
	}
	else
	{
		if (j == 0)
		{
			i = 10;
			j = 5;
		}
		else
		{
			i = 4;
			j = 4;
		}
	}
}

void main(int argc, char** argv)
{
	int i;
	cout << "Enter an integer i: ";
	cin >> i;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');

	cout << "Calling function A" << endl;
	functionA(i);
	
	cout << "Calling function B" << endl;
	functionB(i);
	
	int j = functionC(i);
	cout << "Result of function C is " << j << endl;
	
	functionE(i, j);

	if (functionD(i))
	{
		cout << "Function D returns true" << endl;
	}

	cout << "i = " << i << " j = " << j << endl;

	cin.get(); // Waits for a keypress
}