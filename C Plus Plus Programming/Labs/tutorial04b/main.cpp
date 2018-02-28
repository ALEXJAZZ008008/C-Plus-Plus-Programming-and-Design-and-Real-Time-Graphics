#include <iostream>
using namespace std;

#include "top.h"

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main(int, char**)
{
	Top a, b, c;

	a.SetValue(5);
	b.SetValue(10);

	a.WriteToStream(cout);
	b.WriteToStream(cout);
	c.WriteToStream(cout);

	return CloseProgram();
}