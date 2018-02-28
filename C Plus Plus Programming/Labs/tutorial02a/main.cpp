#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
using namespace std;

/*
* A program that scans through a C++ file looking for a particular variable
* When the variable is found the line number and position within the line are returned
* Comments are ignored
*/

void main(int argc, char **argv)
{ 
	cout << "Enter a search variable: ";

	string variable;
	cin >> variable;

	ifstream fin("sample.txt");
	bool found = false;
	int position;
	int line = 1;
	while(true)
	{
		if (fin.eof())
		{
			break;
		}

		char lineBuffer[256];
		fin.getline(lineBuffer, sizeof(lineBuffer));

		int lengthOfLine = (int)fin.gcount();
		istrstream sin (lineBuffer, lengthOfLine - 1);  // Removes end of line character

		position = 1;
		string word;
		while(true)
		{
			if (!(sin >> word) || ((word[0] == '/') || (word[1] == '/')))
			{
				break;
			}

			if (word.compare(variable) == 0)
			{
				found = true;

				break;
			}

			position++;
		}

		if (found)
		{
			break;
		}

		line++;
	}

	if (found)
	{
		cout << variable << " appears as the " << position << " word on line number " << line << endl;
	}
	else
	{
		cout << variable << " does not appear in the file" << endl;
	}

	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();
}