#include <iostream>
using namespace std;

/**
 * This program reads in a number of integers and counts the times a 
 * predefined value occurs
 *
 * It contains a bug and fails to give the correct output
 */

void main(int argc, char **argv) { 

	int key;
	cout << "Enter the key value: ";
	cin >> key;

	cout << "Enter a sequence of integers, terminating with a letter: ";

	int i, value;
	int counter = 0;
	for (i = 0; cin >> value; i++)
	{
		if (key == value)
		{
			counter++;
		}
	}

	cin.clear(); 

	cout << counter << " of the " << i << " values equal " << key << endl;

	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();
}