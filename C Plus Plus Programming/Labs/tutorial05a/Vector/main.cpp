#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <windows.h>
using namespace std;

/*
    1. find out how long it takes for the following
	   operations to take place for the container - vector
	2. complete the same tasks for container - list
	3. complete the same tasks for container - set
*/

typedef vector<int>::iterator vectorIterator;
typedef list<int>::iterator listIterator;
typedef set<int>::iterator setIterator;

const int LIMIT = 999999;

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

void VectorTest()
{
	vector<int> vector;

	for (int i = 0; i < LIMIT; i++)	// add LIMIT items to the vector
	{
		vector.push_back(i);
	}

	cout << "Completed Vector Add" << endl;

	for (int i = 0; i < LIMIT; i++)	// access all item in the vector
	{
		vector.at(i);
	}

	cout << "Completed Vector Random Access" << endl;

	vectorIterator iterator = vector.begin();

	for (int i = 0; i < LIMIT; i++)	// traverse all items in the vector
	{
		*(iterator++);
	}

	cout << "Completed Vector Traverse Access" << endl;

	for (int i = 0; i < LIMIT; i++)	// delete all items in the vector
	{
		vector.pop_back();
	}

	cout << "Completed Vector Items Remove" << endl;
}

void ListTest()
{
	list<int> list;

	for (int i = 0; i < LIMIT; i++)	// add LIMIT items to the List
	{
		list.push_back(i);
	}

	cout << "Completed List Add" << endl;

	listIterator iterator = list.begin();

	for (int i = 0; i < LIMIT; i++)	// traverse all items in the List
	{
		*(iterator++);
	}

	cout << "Completed List Traverse Access" << endl;

	for (int i = 0; i < LIMIT; i++)	// delete all items in the List
	{
		list.pop_back();
	}

	cout << "Completed List Items Remove" << endl;
}

void SetTest()
{
	set<int> set;

	for (int i = 0; i < LIMIT; i++)	// add LIMIT items to the set
	{
		set.insert(i);
	}

	cout << "Completed Set Add" << endl;

	setIterator iterator = set.begin();

	for (int i = 0; i < LIMIT; i++)	// traverse all items in the set
	{
		*(iterator++);
	}

	cout << "Completed Set Traverse Access" << endl;

	set.clear();

	cout << "Completed Set Items Remove" << endl;
}

int main(int, char**)
{
	LARGE_INTEGER frequency, startCount, endCount;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	VectorTest();

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << LIMIT << " cycles is " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	ListTest();

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << LIMIT << " cycles is " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startCount);

	SetTest();

	QueryPerformanceCounter(&endCount);

	cout << "Duration for " << LIMIT << " cycles is " << ((endCount.QuadPart - startCount.QuadPart) / double(frequency.QuadPart)) << "s" << endl;

	return CloseProgram();
}
