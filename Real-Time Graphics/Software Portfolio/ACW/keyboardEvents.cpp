#include "keyboardEvents.h"


KeyboardEvents::KeyboardEvents() : m_Keys()
{
	// Initialize all the keys to being released and not pressed.
	for (int i = 0; i < m_Keys.size(); i++)
	{
		m_Keys.at(i) = false;
	}
}

KeyboardEvents::KeyboardEvents(const KeyboardEvents &keyboardEvents) : m_Keys(keyboardEvents.GetKeys())
{
	
}

KeyboardEvents & KeyboardEvents::operator = (const KeyboardEvents &keyboardEvents)
{
	if (this != &keyboardEvents)
	{
		m_Keys = keyboardEvents.GetKeys();
	}

	return *this;
}

KeyboardEvents::KeyboardEvents(const KeyboardEvents &&keyboardEvents) : m_Keys(keyboardEvents.GetKeys())
{
	
}

KeyboardEvents & KeyboardEvents::operator = (const KeyboardEvents &&keyboardEvents)
{
	if (this != &keyboardEvents)
	{
		m_Keys = keyboardEvents.GetKeys();
	}

	return *this;
}

KeyboardEvents::~KeyboardEvents()
{
	try
	{

	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void KeyboardEvents::KeyDown(const int key)
{
	// If a key is pressed then save that state in the key array.
	m_Keys.at(key) = true;
}

void KeyboardEvents::KeyUp(const int key)
{
	// If a key is released then clear that state in the key array.
	m_Keys.at(key) = false;
}