#include "fps.h"

FPS::FPS() : m_FPS(0), m_Count(0), m_Start(timeGetTime())
{

}

FPS::FPS(const FPS &fps) : m_FPS(fps.GetFPS()), m_Count(fps.GetCount()), m_Start(fps.GetStart())
{

}

FPS & FPS::operator = (const FPS &fps)
{
	if (this != &fps)
	{
		m_FPS = fps.GetFPS();
		m_Count = fps.GetCount();
		m_Start = fps.GetStart();
	}

	return *this;
}

FPS::FPS(const FPS &&fps) : m_FPS(fps.GetFPS()), m_Count(fps.GetCount()), m_Start(fps.GetStart())
{

}

FPS & FPS::operator = (const FPS &&fps)
{
	if (this != &fps)
	{
		m_FPS = fps.GetFPS();
		m_Count = fps.GetCount();
		m_Start = fps.GetStart();
	}

	return *this;
}

FPS::~FPS()
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

void FPS::Update()
{
	m_Count++;

	if (timeGetTime() >= m_Start + 1000)
	{
		m_FPS = m_Count;

		m_Count = 0;
		m_Start = timeGetTime();
	}
}