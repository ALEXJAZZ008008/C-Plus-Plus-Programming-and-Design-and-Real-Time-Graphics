#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
* Partially completed program
* The program should parse a text file.
*
* The text file contains a sequence of nested objects, where each object is
* delimited by characters { and }
* Attributes within the objects consist of a name followed by at least one white space followed by a
* set of parameters delimited by characters ( and ).
* e.g colour (5)
* A comma is used to separate multiple parameters
* e.g. position (3,5)
* At least one white space is used to separate attributes
* e.g. colour (5) position (3,5)
* The full set of named attributes are:
*		colour (integer)
*		position (integer, integer)
*		size (integer)
*
* Requirement
* 1. Copy the file to a output file
* 2. Locate the object with the largest size.  Print out the level within the
*	object hierarchy.  Assume the outer most object is level 1
*/

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

void WriteToFile(ofstream &fileOut, string attribute)
{
	fileOut << attribute;
}

void WriteToFile(ofstream &fileOut, int level, string attribute)
{
	for (int i = 0; i < level; i++)
	{
		fileOut << "\t";
	}

	WriteToFile(fileOut, attribute);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <input filename> <output filename>" << endl;

		return CloseProgram();
	}

	ifstream fileIn(argv[1]);

	if (!fileIn)
	{
		cerr << "Error: Failed to open file " << argv[1] << " for reading" << endl;

		return CloseProgram();
	}

	ofstream fileOut(argv[2]);

	if (!fileOut)
	{
		cerr << "Error: Failed to open file " << argv[2] << " for writing" << endl;

		return CloseProgram();
	}

	string attribute;
	int level = 0, maxSize = 0, levelOfMaxSizeObject = 0;

	while (fileIn >> attribute)
	{
		if (attribute.find("{") != string::npos)
		{
			attribute += "\r\n";

			WriteToFile(fileOut, level, attribute);

			level++;

			continue;
		}

		if (attribute.find("}") != string::npos)
		{
			level--;

			attribute += "\r\n";

			WriteToFile(fileOut, level, attribute);

			continue;
		}

		WriteToFile(fileOut, level, attribute);

		if (attribute.find("size") != string::npos)
		{
			fileIn >> attribute;

			int endOfStringPosition = attribute.find(")");

			string stringParameter;

			for (int i = 1; i < endOfStringPosition; i++)
			{
				stringParameter += attribute[i];
			}

			int intParameter = stoi(stringParameter);

			if (intParameter > maxSize)
			{
				maxSize = intParameter;
				levelOfMaxSizeObject = level + 1;
			}
		}
		else
		{
			fileIn >> attribute;
		}

		attribute += "\r\n";

		WriteToFile(fileOut, attribute);

		continue;
	}

	cout << "Largest object of size " << maxSize << " is located at level " << levelOfMaxSizeObject;

	return CloseProgram();
}