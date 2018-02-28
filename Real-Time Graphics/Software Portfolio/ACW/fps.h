#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class FPS
{
public:
	FPS();
	FPS(const FPS &);
	FPS & operator = (const FPS &);
	FPS(const FPS &&);
	FPS & operator = (const FPS &&);
	~FPS();

	const int GetFPS() const
	{
		return m_FPS;
	}

	const int GetCount() const
	{
		return m_Count;
	}

	const unsigned long GetStart() const
	{
		return m_Start;
	}

	void SetFPS(const int fps)
	{
		m_FPS = fps;
	}

	void SetCount(const int count)
	{
		m_Count = count;
	}

	void SetStart(const unsigned long start)
	{
		m_Start = start;
	}

	void Update();

private:
	int m_FPS, m_Count;
	unsigned long m_Start;
};