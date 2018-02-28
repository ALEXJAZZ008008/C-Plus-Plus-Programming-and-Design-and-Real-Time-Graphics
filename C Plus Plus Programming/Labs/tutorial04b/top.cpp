#include "top.h"

Top::Top()
{
	SetValue(0);
}

int Top::GetValue() const
{
	return m_value;
}

void Top::SetValue(int value)
{
	m_value = value;
}

void Top::WriteToStream(ostream &stream)
{
	stream << GetValue() << endl;
}