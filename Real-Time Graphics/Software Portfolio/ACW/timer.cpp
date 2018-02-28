#include "timer.h"

Timer::Timer() : m_Start(), m_Frequency(), m_Ticks(0.0f), m_DT(0.0f)
{
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&m_Frequency));

	m_Ticks = static_cast<float>(m_Frequency / 1000);

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&m_Start));
}

Timer::Timer(const Timer &timer) : m_Start(timer.GetStart()), m_Frequency(timer.GetFrequency()), m_Ticks(timer.GetTicks()), m_DT(timer.GetDT())
{

}

Timer & Timer::operator = (const Timer &timer)
{
	if (this != &timer)
	{
		m_Start = timer.GetStart();
		m_Frequency = timer.GetFrequency();

		m_Ticks = timer.GetTicks();
		m_DT = timer.GetDT();
	}

	return *this;
}

Timer::Timer(const Timer &&timer) : m_Start(timer.GetStart()), m_Frequency(timer.GetFrequency()), m_Ticks(timer.GetTicks()), m_DT(timer.GetDT())
{

}

Timer & Timer::operator = (const Timer &&timer)
{
	if (this != &timer)
	{
		m_Start = timer.GetStart();
		m_Frequency = timer.GetFrequency();

		m_Ticks = timer.GetTicks();
		m_DT = timer.GetDT();
	}

	return *this;
}

Timer::~Timer()
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

void Timer::Update()
{
	INT64 time;

	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&time));

	m_DT = (time / m_Ticks) / 1000;

	m_Start = time;
}