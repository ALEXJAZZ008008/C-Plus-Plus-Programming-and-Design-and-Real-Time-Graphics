#pragma once

#include <windows.h>
#include <directxmath.h>
#include <iostream>
#include <array>
#include "fps.h"
#include "cpu.h"
#include "timer.h"
#include "keyboardEvents.h"
#include "graphics.h"

using namespace std;
using namespace DirectX;

class Scene
{
public:
	Scene();
	explicit Scene(const char *);
	Scene(const Scene &);
	Scene & operator = (const Scene &);
	Scene(const Scene &&);
	Scene & operator = (const Scene &&);
	~Scene();

	const FPS * GetFPS() const
	{
		return m_FPS;
	}

	const CPU * GetCPU() const
	{
		return m_CPU;
	}

	const Timer * GetTimer() const
	{
		return m_Timer;
	}

	const KeyboardEvents * GetKeyboardEvents() const
	{
		return m_KeyboardEvents;
	}

	const Graphics * GetGraphics() const
	{
		return m_Graphics;
	}

	const LPCSTR GetApplicationName() const
	{
		return m_ApplicationName;
	}

	const HINSTANCE GetHInstance() const
	{
		return m_HInstance;
	}

	const HWND GetHWND() const
	{
		return m_HWND;
	}

	const array<bool, 255> &GetKeyboardInterstate() const
	{
		return m_KeyboardInterstate;
	}

	const float GetTimeScale() const
	{
		return m_TimeScale;
	}

	void SetFPS(FPS * const fps)
	{
		m_FPS = fps;
	}

	void SetCPU(CPU * const cpu)
	{
		m_CPU = cpu;
	}

	void SetTimer(Timer * const timer)
	{
		m_Timer = timer;
	}

	void SetKeyboardEvents(KeyboardEvents * const keyboardEvents)
	{
		m_KeyboardEvents = keyboardEvents;
	}

	void SetGraphics(Graphics * const graphics)
	{
		m_Graphics = graphics;
	}

	void SetApplicationName(const LPCSTR &applicationName)
	{
		m_ApplicationName = applicationName;
	}

	void SetHInstance(const HINSTANCE &hInstance)
	{
		m_HInstance = hInstance;
	}

	void SetHWND(const HWND &hwnd)
	{
		m_HWND = hwnd;
	}

	void SetKeyboardInterstate(const array<bool, 255> &keyboardInterstate)
	{
		m_KeyboardInterstate = keyboardInterstate;
	}

	void SetTimeScale(const float timeScale)
	{
		m_TimeScale = timeScale;
	}

	bool Run();
	bool Update();
	void KeyboardUpdateCamera();
	void KeyboardUpdateObjects();

	LRESULT CALLBACK ProgramCallBack(const HWND, const UINT, const WPARAM, const LPARAM);

private:
	FPS *m_FPS;
	CPU *m_CPU;
	Timer *m_Timer;
	KeyboardEvents *m_KeyboardEvents;
	Graphics *m_Graphics;
	LPCSTR m_ApplicationName;
	HINSTANCE m_HInstance;
	HWND m_HWND;
	array<bool, 255> m_KeyboardInterstate;
	float m_TimeScale;
};

static LRESULT CALLBACK WindowsCallBack(const HWND, const UINT, const WPARAM, const LPARAM);
static Scene *This;