#include <iostream>
#include <string>
#include <windows.h>  // required for QueryPerformanceCounter()
using namespace std;

const int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

string Concat(string a, string b, string c)
{
	return a + b + c;
}

string Concat2(string &a, string &b, string &c)
{
	return a + b + c;
}

string &Concat3(string &a, string &b, string &c, string &d)
{
	d = a + b + c;

	return d;
}

/**
 * Program experiments with the concatenation of strings
 */

int main(int argc, char** argv)
{
	string d;
	string a = "Hello", b = " ", c = "World";
	int limit = 999999;

	LARGE_INTEGER frequency, startCount, endCount;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	for (int i = 0; i < limit; i++)
	{
		d = Concat(a, b, c);
	}

	QueryPerformanceCounter(&endCount);
	
	cout << "Duration for " << limit << " cycles is " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;
	cout << "Result string is \"" << d << "\"" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	for (int i = 0; i < limit; i++)
	{
		d = Concat2(a, b, c);
	}

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << limit << " cycles is " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;
	cout << "Result string is \"" << d << "\"" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	for (int i = 0; i < limit; i++)
	{
		d = Concat3(a, b, c, d);
	}

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << limit << " cycles is " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;
	cout << "Result string is \"" << d << "\"" << endl;

	return CloseProgram();
}