#pragma once

#include <array>
#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class KeyboardEvents
{
public:
	KeyboardEvents();
	KeyboardEvents(const KeyboardEvents &);
	KeyboardEvents & operator = (const KeyboardEvents &);
	KeyboardEvents(const KeyboardEvents &&);
	KeyboardEvents & operator = (const KeyboardEvents &&);
	~KeyboardEvents();

	const array<bool, 255> & GetKeys() const
	{
		return m_Keys;
	}

	void SetKeys(const array<bool, 255> &keys)
	{
		m_Keys = keys;
	}

	void KeyDown(const int);
	void KeyUp(const int);

private:
	array<bool, 255> m_Keys;
};