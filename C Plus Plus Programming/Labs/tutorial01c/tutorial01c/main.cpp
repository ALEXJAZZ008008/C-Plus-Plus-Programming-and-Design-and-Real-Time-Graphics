#include <iostream>
using namespace std;

/**
 * This program reads in a number of integers and counts the times a 
 * number one, two or three occurs
 *
 * It contains a bug and fails to give the correct output
 */

void main(int argc, char **argv)
{ 
	int equals1 = 0, equals2 = 0, equals3 = 0;

	cout << "Enter a list of integers, terminating with a letter: ";

	int value;
	while (cin >> value)
	{
		switch (value)
		{
			case 1:

				equals1++;
				break;
				
			case 2:

				equals2++;
				break;

			case 3:

				equals3++;
				break;
		}
	}

	cin.clear();

	cout << equals1 << " inputs equals 1" << endl << equals2 << " inputs equals 2" << endl << equals3 << " inputs equals 3" << endl;

	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();
}