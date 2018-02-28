#pragma once

#include <windows.h>
#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class Timer
{
public:
	Timer();
	Timer(const Timer &);
	Timer & operator = (const Timer &);
	Timer(const Timer &&);
	Timer & operator = (const Timer &&);
	~Timer();

	const INT64 GetStart() const
	{
		return m_Start;
	}

	const INT64 GetFrequency() const
	{
		return m_Frequency;
	}

	const float GetTicks() const
	{
		return m_Ticks;
	}

	const float GetDT() const
	{
		return m_DT;
	}

	void SetStart(const INT64 &start)
	{
		m_Start = start;
	}

	void SetFrequency(const INT64 &frequency)
	{
		m_Frequency = frequency;
	}

	void SetTicks(const float ticks)
	{
		m_Ticks = ticks;
	}

	void SetDT(const float dt)
	{
		m_DT = dt;
	}

	void Update();

private:
	INT64 m_Start, m_Frequency;
	float m_Ticks, m_DT;
};