#include "cpu.h"

CPU::CPU() : m_HQuery(nullptr), m_HCounter(nullptr), m_PreviousTime(GetTickCount()), m_CPU(0)
{
	PdhOpenQuery(nullptr, 0, &m_HQuery);

	PdhAddCounter(m_HQuery, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_HCounter);
}

CPU::CPU(const CPU &cpu) : m_HQuery(cpu.GetHQuery()), m_HCounter(cpu.GetHCounter()), m_PreviousTime(cpu.GetPreviousTime()), m_CPU(cpu.GetCPU())
{
	
}

CPU & CPU::operator = (const CPU &cpu)
{
	if (this != &cpu)
	{
		m_HQuery = cpu.GetHQuery();

		m_HCounter = cpu.GetHCounter();

		m_PreviousTime = cpu.GetPreviousTime();
		m_CPU = cpu.GetCPU();
	}

	return *this;
}

CPU::CPU(const CPU &&cpu) : m_HQuery(cpu.GetHQuery()), m_HCounter(cpu.GetHCounter()), m_PreviousTime(cpu.GetPreviousTime()), m_CPU(cpu.GetCPU())
{

}

CPU & CPU::operator = (const CPU &&cpu)
{
	if (this != &cpu)
	{
		m_HQuery = cpu.GetHQuery();

		m_HCounter = cpu.GetHCounter();

		m_PreviousTime = cpu.GetPreviousTime();
		m_CPU = cpu.GetCPU();
	}

	return *this;
}

CPU::~CPU()
{
	try
	{
		PdhCloseQuery(m_HQuery);
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void CPU::Update()
{
	if (GetTickCount() > m_PreviousTime + 1000)
	{
		PdhCollectQueryData(m_HQuery);

		PDH_FMT_COUNTERVALUE counter;

		PdhGetFormattedCounterValue(m_HCounter, static_cast<DWORD>(0x00000100), nullptr, &counter);

		m_CPU = counter.longValue;

		m_PreviousTime = GetTickCount();
	}
}