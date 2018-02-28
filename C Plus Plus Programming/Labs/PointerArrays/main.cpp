#include <iostream>
using namespace std;

#include "list.h"
#include "list2d.h"

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main(int, char**)
{
	cout << "Input size of 2d array: ";

	int size[2];

	cin >> size[0] >> size[1];

	cout << "Input values for 2d array: ";

	List2d list2d;

	int value;

	for (int i = 0; i < size[0]; i++)
	{
		List list = *new List();

		for (int j = 0; j < size[1]; j++)
		{
			cin >> value;

			list.AddNode(value);
		}

		list2d.AddNode(list);
	}

	cout << "values in 2d array:";

	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 0; j < size[1]; j++)
		{
			cout << " " << list2d.GetElement(i)->GetItem().GetElement(j)->GetItem();
		}
	}

	list2d.ClearList();

	return CloseProgram();
}