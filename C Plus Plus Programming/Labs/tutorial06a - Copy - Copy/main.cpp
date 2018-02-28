#include <iostream>
using namespace std;

#include "list.h"

int CloseProgram()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cin.get();

	return -1;
}

int main(int, char**)
{
	List<int> list;

	//list.AddNode(4);
	//list.AddNode(10);
	//list.AddNode(2);
	//list.AddNode(1);

	//int item = list.GetElement(2)->GetItem();

	//cout << "Item at 2 is " << item << endl;

	//cout << "Queue contents:" << endl;

	//while (list.GetSize())
	//{
	//	cout << list.GetHead() << endl;

	//	list.RemoveNode();
	//}

	return CloseProgram();
}