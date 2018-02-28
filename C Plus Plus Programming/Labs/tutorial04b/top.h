#pragma once

#include <iostream>
using namespace std;

//TODO: Add appropriate include statements

class Top 
{
public:
	// Constructor
	Top();

	// Selector
	int GetValue() const;

	// Modifier
	void SetValue(int value);

	void WriteToStream(ostream &stream);

private:
	// Data member
	int m_value;
};
