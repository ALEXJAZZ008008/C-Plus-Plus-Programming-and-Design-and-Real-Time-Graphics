#pragma once

#include <Pdh.h>
#include <directxmath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

class CPU
{
public:
	CPU();
	CPU(const CPU &);
	CPU & operator = (const CPU &);
	CPU(const CPU &&);
	CPU & operator = (const CPU &&);
	~CPU();

	const HQUERY GetHQuery() const
	{
		return m_HQuery;
	}

	const HCOUNTER GetHCounter() const
	{
		return m_HCounter;
	}

	const unsigned long GetPreviousTime() const
	{
		return m_PreviousTime;
	}

	const unsigned long GetCPU() const
	{
		return m_CPU;
	}

	void SetHQuery(const HQUERY &hQuery)
	{
		m_HQuery = hQuery;
	}

	void SetHCounter(const HCOUNTER &hCounter)
	{
		m_HCounter = hCounter;
	}

	void SetPreviousTime(const unsigned long previousTime)
	{
		m_PreviousTime = previousTime;
	}

	void SetCPU(const unsigned long cpu)
	{
		m_CPU = cpu;
	}

	void Update();

private:
	HQUERY m_HQuery;
	HCOUNTER m_HCounter;
	unsigned long m_PreviousTime, m_CPU;
};