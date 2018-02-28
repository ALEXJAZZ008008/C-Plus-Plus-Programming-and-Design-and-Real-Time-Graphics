#include "scene.h"

Scene::Scene() : m_FPS(new FPS()), m_CPU(new CPU()), m_Timer(new Timer()), m_KeyboardEvents(new KeyboardEvents()), m_Graphics(nullptr), m_ApplicationName("ACW"), m_HInstance(GetModuleHandle(nullptr)), m_HWND(nullptr), m_KeyboardInterstate(), m_TimeScale(1.0f)
{
	This = nullptr;

	WNDCLASSEX wndClassEx =
	{
		sizeof(wndClassEx)
	};

	// Setup the windows class with default settings.
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClassEx.lpfnWndProc = WindowsCallBack;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = m_HInstance;
	wndClassEx.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClassEx.hIconSm = wndClassEx.hIcon;
	wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wndClassEx.lpszMenuName = nullptr;
	wndClassEx.lpszClassName = m_ApplicationName;
	wndClassEx.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wndClassEx);

	// Determine the resolution of the clients desktop screen.
	XMFLOAT2 screen = XMFLOAT2(static_cast<float>(GetSystemMetrics(SM_CXSCREEN)), static_cast<float>(GetSystemMetrics(SM_CYSCREEN)));

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	DEVMODE devMode =
	{
		sizeof(devMode)
	};

	// Set the screen to maximum size of the users desktop and 32bit.
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth = static_cast<long>(screen.x);
	devMode.dmPelsHeight = static_cast<long>(screen.y);
	devMode.dmBitsPerPel = 32;
	devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Change the display settings to full screen.
	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

	// Set the position of the window to the top left corner.
	XMFLOAT2 const position = XMFLOAT2(0, 0);

	// Create the window with the screen settings and get the handle to it.
	m_HWND = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(screen.x), static_cast<int>(screen.y), nullptr, nullptr, m_HInstance, nullptr);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_HWND, SW_SHOW);
	SetForegroundWindow(m_HWND);
	SetFocus(m_HWND);

	// Create and initialise the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new Graphics(m_HWND, screen, XMFLOAT2(1000.0f, 0.001f));

	// Get an external pointer to this object.	
	This = this;
}

Scene::Scene(const char *graphicsFilename) : m_FPS(new FPS()), m_CPU(new CPU()), m_Timer(new Timer()), m_KeyboardEvents(new KeyboardEvents()), m_Graphics(nullptr), m_ApplicationName("ACW"), m_HInstance(GetModuleHandle(nullptr)), m_HWND(nullptr), m_KeyboardInterstate(), m_TimeScale(1.0f)
{
	This = nullptr;

	WNDCLASSEX wndClassEx =
	{
		sizeof(wndClassEx)
	};

	// Setup the windows class with default settings.
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClassEx.lpfnWndProc = WindowsCallBack;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = m_HInstance;
	wndClassEx.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClassEx.hIconSm = wndClassEx.hIcon;
	wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wndClassEx.lpszMenuName = nullptr;
	wndClassEx.lpszClassName = m_ApplicationName;
	wndClassEx.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wndClassEx);

	// Determine the resolution of the clients desktop screen.
	XMFLOAT2 screen = XMFLOAT2(static_cast<float>(GetSystemMetrics(SM_CXSCREEN)), static_cast<float>(GetSystemMetrics(SM_CYSCREEN)));

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	DEVMODE devMode =
	{
		sizeof(devMode)
	};

	// Set the screen to maximum size of the users desktop and 32bit.
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth = static_cast<long>(screen.x);
	devMode.dmPelsHeight = static_cast<long>(screen.y);
	devMode.dmBitsPerPel = 32;
	devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Change the display settings to full screen.
	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

	// Set the position of the window to the top left corner.
	XMFLOAT2 const position = XMFLOAT2(0, 0);

	// Create the window with the screen settings and get the handle to it.
	m_HWND = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(screen.x), static_cast<int>(screen.y), nullptr, nullptr, m_HInstance, nullptr);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_HWND, SW_SHOW);
	SetForegroundWindow(m_HWND);
	SetFocus(m_HWND);

	GraphicsLoader *graphicsLoader = new GraphicsLoader(graphicsFilename);

	// Create and initialise the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new Graphics(m_HWND, screen, XMFLOAT2(1000.0f, 0.001f), graphicsLoader);

	delete graphicsLoader;

	// Get an external pointer to this object.	
	This = this;
}

Scene::Scene(const Scene &scene) : m_FPS(const_cast<FPS *>(scene.GetFPS())), m_CPU(const_cast<CPU *>(scene.GetCPU())), m_Timer(const_cast<Timer *>(scene.GetTimer())), m_KeyboardEvents(const_cast<KeyboardEvents *>(scene.GetKeyboardEvents())), m_Graphics(const_cast<Graphics *>(scene.GetGraphics())), m_ApplicationName(scene.GetApplicationName()), m_HInstance(scene.GetHInstance()), m_HWND(scene.GetHWND()), m_KeyboardInterstate(scene.GetKeyboardInterstate()), m_TimeScale(scene.GetTimeScale())
{
	This = this;
}

Scene & Scene::operator = (const Scene &scene)
{
	if (this != &scene)
	{
		m_FPS = const_cast<FPS *>(scene.GetFPS());
		m_CPU = const_cast<CPU *>(scene.GetCPU());
		m_Timer = const_cast<Timer *>(scene.GetTimer());
		m_KeyboardEvents = const_cast<KeyboardEvents *>(scene.GetKeyboardEvents());
		m_Graphics = const_cast<Graphics *>(scene.GetGraphics());

		m_ApplicationName = scene.GetApplicationName();
		m_HInstance = scene.GetHInstance();
		m_HWND = scene.GetHWND();

		m_KeyboardInterstate = scene.GetKeyboardInterstate();

		m_TimeScale = scene.GetTimeScale();

		This = this;
	}

	return *this;
}

Scene::Scene(const Scene &&scene) : m_FPS(const_cast<FPS *>(scene.GetFPS())), m_CPU(const_cast<CPU *>(scene.GetCPU())), m_Timer(const_cast<Timer *>(scene.GetTimer())), m_KeyboardEvents(const_cast<KeyboardEvents *>(scene.GetKeyboardEvents())), m_Graphics(const_cast<Graphics *>(scene.GetGraphics())), m_ApplicationName(scene.GetApplicationName()), m_HInstance(scene.GetHInstance()), m_HWND(scene.GetHWND()), m_KeyboardInterstate(scene.GetKeyboardInterstate()), m_TimeScale(scene.GetTimeScale())
{
	This = this;
}

Scene & Scene::operator = (const Scene &&scene)
{
	if (this != &scene)
	{
		m_FPS = const_cast<FPS *>(scene.GetFPS());
		m_CPU = const_cast<CPU *>(scene.GetCPU());
		m_Timer = const_cast<Timer *>(scene.GetTimer());
		m_KeyboardEvents = const_cast<KeyboardEvents *>(scene.GetKeyboardEvents());
		m_Graphics = const_cast<Graphics *>(scene.GetGraphics());

		m_ApplicationName = scene.GetApplicationName();
		m_HInstance = scene.GetHInstance();
		m_HWND = scene.GetHWND();

		m_KeyboardInterstate = scene.GetKeyboardInterstate();

		m_TimeScale = scene.GetTimeScale();

		This = this;
	}

	return *this;
}

Scene::~Scene()
{
	try
	{
		delete m_FPS;

		delete m_CPU;

		delete m_Timer;

		// Release the graphics object.
		delete m_Graphics;

		// Release the input object.
		delete m_KeyboardEvents;

		// Shutdown the window.
		// Fix the display settings.
		ChangeDisplaySettings(nullptr, 0);

		// Remove the window.
		DestroyWindow(m_HWND);

		// Remove the application instance.
		UnregisterClass(m_ApplicationName, m_HInstance);
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

bool Scene::Run()
{
	MSG msg =
	{

	};

	// Loop until there is a quit message from the window or the user.
	while (true)
	{
		try
		{
			// Handle the windows messages.
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// If windows signals to end the application then exit out.
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// Otherwise do the frame processing.
				if (!Update())
				{
					break;
				}
			}
		}
		catch (exception &e)
		{
			cout << e.what();
		}
	}

	return false;
}

bool Scene::Update()
{
	// Check if the user pressed escape and wants to exit the application.
	if (m_KeyboardEvents->GetKeys().at(VK_ESCAPE))
	{
		return false;
	}
	else
	{
		m_FPS->Update();
		m_CPU->Update();
		m_Timer->Update();

		KeyboardUpdateCamera();
		KeyboardUpdateObjects();

		// Do the frame processing for the graphics object.
		if (!m_Graphics->Update(m_FPS->GetFPS(), static_cast<int>(m_CPU->GetCPU()), m_Timer->GetDT() * m_TimeScale, m_TimeScale))
		{
			return false;
		}
	}

	return true;
}

void Scene::KeyboardUpdateCamera()
{
	View * const temporaryView = const_cast<View *>(m_Graphics->GetView());

	if (m_KeyboardEvents->GetKeys().at(VK_F1))
	{
		if (!m_KeyboardInterstate.at(VK_F1))
		{
			temporaryView->SetViewToOutside();

			m_Graphics->SetTrackingViewBool(false);
			m_Graphics->SetViewPositionBool(false);
			m_Graphics->SetViewEyePositionBool(false);

			m_KeyboardInterstate.at(VK_F1) = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at(VK_F1) = false;
	}

	if (m_KeyboardEvents->GetKeys().at(VK_F2))
	{
		if (!m_KeyboardInterstate.at(VK_F2))
		{
			temporaryView->SetViewToInside();

			m_Graphics->SetTrackingViewBool(true);
			m_Graphics->SetViewPositionBool(false);
			m_Graphics->SetViewEyePositionBool(false);
			
			m_KeyboardInterstate.at(VK_F2) = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at(VK_F2) = false;
	}

	if (m_KeyboardEvents->GetKeys().at(VK_F3))
	{
		if (!m_KeyboardInterstate.at(VK_F3))
		{
			temporaryView->SetViewToOutside();

			m_Graphics->SetTrackingViewBool(true);
			m_Graphics->SetViewPositionBool(true);
			m_Graphics->SetViewEyePositionBool(false);

			m_KeyboardInterstate.at(VK_F3) = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at(VK_F3) = false;
	}

	if (m_KeyboardEvents->GetKeys().at(VK_F4))
	{
		if (!m_KeyboardInterstate.at(VK_F4))
		{
			temporaryView->SetViewToOutside();

			m_Graphics->SetTrackingViewBool(true);
			m_Graphics->SetViewPositionBool(true);
			m_Graphics->SetViewEyePositionBool(true);

			m_KeyboardInterstate.at(VK_F4) = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at(VK_F4) = false;
	}

	if (m_KeyboardEvents->GetKeys().at(VK_CONTROL))
	{
		if (m_KeyboardEvents->GetKeys().at(VK_UP))
		{
			temporaryView->SetPositionZ(temporaryView->GetPositionZ() + (cosf((temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
			temporaryView->SetPositionX(temporaryView->GetPositionX() + (sinf((temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
		}

		if (m_KeyboardEvents->GetKeys().at(VK_DOWN))
		{
			temporaryView->SetPositionZ(temporaryView->GetPositionZ() - (cosf((temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
			temporaryView->SetPositionX(temporaryView->GetPositionX() - (sinf((temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
		}

		if (m_KeyboardEvents->GetKeys().at(VK_LEFT))
		{
			temporaryView->SetPositionX(temporaryView->GetPositionX() - (cosf(- (temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
			temporaryView->SetPositionZ(temporaryView->GetPositionZ() - (sinf(- (temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
		}

		if (m_KeyboardEvents->GetKeys().at(VK_RIGHT))
		{
			temporaryView->SetPositionX(temporaryView->GetPositionX() + (cosf(- (temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
			temporaryView->SetPositionZ(temporaryView->GetPositionZ() + (sinf(- (temporaryView->GetRotationY() * (3.141592653589793238462643383279502884f / 180.0f))) * 0.025f));
		}

		if (m_KeyboardEvents->GetKeys().at(VK_PRIOR))
		{
			temporaryView->SetPositionY(temporaryView->GetPositionY() + 0.025f);
		}

		if (m_KeyboardEvents->GetKeys().at(VK_NEXT))
		{
			temporaryView->SetPositionY(temporaryView->GetPositionY() - 0.025f);
		}
	}
	else
	{
		if (m_KeyboardEvents->GetKeys().at(VK_UP))
		{
			temporaryView->SetRotationX(temporaryView->GetRotationX() - 0.5f);

			if (temporaryView->GetRotationX() < 0.0f)
			{
				temporaryView->SetRotationX(360.0f);
			}
		}

		if (m_KeyboardEvents->GetKeys().at(VK_DOWN))
		{
			temporaryView->SetRotationX(temporaryView->GetRotationX() + 0.5f);

			if (temporaryView->GetRotationX() > 360.0f)
			{
				temporaryView->SetRotationX(0.0f);
			}
		}

		if (m_KeyboardEvents->GetKeys().at(VK_LEFT))
		{
			temporaryView->SetRotationY(temporaryView->GetRotationY() - 0.5f);

			if (temporaryView->GetRotationY() < 0.0f)
			{
				temporaryView->SetRotationY(360.0f);
			}
		}

		if (m_KeyboardEvents->GetKeys().at(VK_RIGHT))
		{
			temporaryView->SetRotationY(temporaryView->GetRotationY() + 0.5f);

			if (temporaryView->GetRotationY() > 360.0f)
			{
				temporaryView->SetRotationY(0.0f);
			}
		}
	}
}

void Scene::KeyboardUpdateObjects()
{
	if (m_KeyboardEvents->GetKeys().at('E'))
	{
		if (!m_KeyboardInterstate.at('E'))
		{
			Model * const * const temporaryModel = m_Graphics->GetModels().data();

			temporaryModel[0]->SetPosition(temporaryModel[0]->GetInitialPosition());
			temporaryModel[0]->SetRotation(temporaryModel[0]->GetInitialRotation());

			temporaryModel[1]->SetPosition(temporaryModel[1]->GetInitialPosition());
			temporaryModel[1]->SetRotation(temporaryModel[1]->GetInitialRotation());

			temporaryModel[2]->SetPosition(temporaryModel[2]->GetInitialPosition());
			temporaryModel[2]->SetRotation(temporaryModel[2]->GetInitialRotation());

			m_Graphics->SetTimeOffsetBool(false);
			m_Graphics->SetUpdateBool(false);
			m_Graphics->SetMoveBool(false);
			m_Graphics->SetTimeElapsed(0.0f);
			m_Graphics->SetTimeOffset(0.0f);
			m_Graphics->SetObjectState(0.0f);
			m_Graphics->SetUpdateCount(0);

			for (int i = 0; i < m_Graphics->GetModels().size(); i++)
			{
				m_Graphics->GetModels().at(i)->SetStartPositionBool(false);
				m_Graphics->GetModels().at(i)->SetStartRotationBool(false);
			}

			m_KeyboardInterstate.at('E') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('E') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('R'))
	{
		if (!m_KeyboardInterstate.at('R'))
		{
			m_TimeScale = 1.0f;

			View * const temporaryView = const_cast<View *>(m_Graphics->GetView());

			temporaryView->SetInitialPosition(0.0f, 1.0f, -13.0f);
			temporaryView->SetPosition(0.0f, 1.0f, -13.0f);
			temporaryView->SetInitialRotation(0.0f, 0.0f, 0.0f);
			temporaryView->SetRotation(0.0f, 0.0f, 0.0f);

			Model * const * const temporaryModel = m_Graphics->GetModels().data();

			temporaryModel[0]->SetPosition(temporaryModel[0]->GetInitialPosition());
			temporaryModel[0]->SetRotation(temporaryModel[0]->GetInitialRotation());

			temporaryModel[1]->SetPosition(temporaryModel[1]->GetInitialPosition());
			temporaryModel[1]->SetRotation(temporaryModel[1]->GetInitialRotation());

			temporaryModel[2]->SetPosition(temporaryModel[2]->GetInitialPosition());
			temporaryModel[2]->SetRotation(temporaryModel[2]->GetInitialRotation());

			const vector<Particle> temporaryParticlesParticles;

			Particles * const temporaryParticles = const_cast<Particles *>(m_Graphics->GetParticles());

			temporaryParticles->SetParticles(temporaryParticlesParticles);

			m_Graphics->SetPauseBool(false);
			m_Graphics->SetTimeOffsetBool(false);
			m_Graphics->SetTrackingViewBool(false);
			m_Graphics->SetViewPositionBool(false);
			m_Graphics->SetViewEyePositionBool(false);
			m_Graphics->SetUpdateBool(false);
			m_Graphics->SetMoveBool(false);
			m_Graphics->SetKeyStateBool(false);
			m_Graphics->SetHUDBool(false);
			m_Graphics->SetEyeBool(false);
			m_Graphics->SetStickShadowBool(false);
			m_Graphics->SetMultipleShadowBool(false);
			m_Graphics->SetMovingShadowBool(false);
			m_Graphics->SetLightMarkerBool(false);
			m_Graphics->SetTimeElapsed(0.0f);
			m_Graphics->SetTimeOffset(0.0f);
			m_Graphics->SetObjectState(0.0f);
			m_Graphics->SetUpdateCount(0);
			m_Graphics->SetRenderState(0.0f);

			for (int i = 0; i < m_Graphics->GetModels().size(); i++)
			{
				m_Graphics->GetModels().at(i)->SetStartPositionBool(false);
				m_Graphics->GetModels().at(i)->SetStartRotationBool(false);
			}

			m_KeyboardInterstate.at('R') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('R') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('P'))
	{
		if (!m_KeyboardInterstate.at('P'))
		{
			if (m_Graphics->GetPauseBool())
			{
				m_Graphics->SetPauseBool(false);
			}
			else
			{
				m_Graphics->SetPauseBool(true);
			}

			m_KeyboardInterstate.at('P') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('P') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('T'))
	{
		if (!m_KeyboardInterstate.at('T'))
		{
			if (m_KeyboardEvents->GetKeys().at(VK_SHIFT))
			{
				m_TimeScale += 0.1f;
			}
			else
			{
				m_TimeScale -= 0.1f;

				if (m_TimeScale < 0.0f)
				{
					m_TimeScale = 0.0f;
				}
			}

			m_KeyboardInterstate.at('T') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('T') = false;
	}

	if (m_KeyboardEvents->GetKeys().at(VK_F5))
	{
		if (!m_KeyboardInterstate.at(VK_F5))
		{
			m_Graphics->SetRenderState(m_Graphics->GetRenderState() + 1.0f);

			if (m_Graphics->GetRenderState() > 3.0f)
			{
				m_Graphics->SetRenderState(0.0f);
			}

			m_KeyboardInterstate.at(VK_F5) = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at(VK_F5) = false;
	}

	if (m_KeyboardEvents->GetKeys().at(VK_F12) || m_KeyboardEvents->GetKeys().at('F'))
	{
		if (!m_KeyboardInterstate.at(VK_F12))
		{
			if (m_Graphics->GetObjectState() < 1.0f)
			{
				m_Graphics->SetObjectState(m_Graphics->GetObjectState() + 1.0f);
			}

			m_KeyboardInterstate.at(VK_F12) = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at(VK_F12) = false;
	}

	if (m_KeyboardEvents->GetKeys().at('S'))
	{
		if (!m_KeyboardInterstate.at('S'))
		{
			if (m_Graphics->GetHUDBool())
			{
				m_Graphics->SetHUDBool(false);
			}
			else
			{
				m_Graphics->SetHUDBool(true);
			}

			m_KeyboardInterstate.at('S') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('S') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('Z'))
	{
		if (!m_KeyboardInterstate.at('Z'))
		{
			if (m_Graphics->GetEyeBool())
			{
				m_Graphics->SetEyeBool(false);
			}
			else
			{
				m_Graphics->SetEyeBool(true);
			}

			m_KeyboardInterstate.at('Z') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('Z') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('X'))
	{
		if (!m_KeyboardInterstate.at('X'))
		{
			if (m_Graphics->GetStickShadowBool())
			{
				m_Graphics->SetStickShadowBool(false);
			}
			else
			{
				m_Graphics->SetStickShadowBool(true);
			}

			m_KeyboardInterstate.at('X') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('X') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('C'))
	{
		if (!m_KeyboardInterstate.at('C'))
		{
			if (m_Graphics->GetMultipleShadowBool())
			{
				m_Graphics->SetMultipleShadowBool(false);
			}
			else
			{
				m_Graphics->SetMultipleShadowBool(true);
			}

			m_KeyboardInterstate.at('C') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('C') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('V'))
	{
		if (!m_KeyboardInterstate.at('V'))
		{
			if (m_Graphics->GetMovingShadowBool())
			{
				m_Graphics->SetMovingShadowBool(false);
			}
			else
			{
				m_Graphics->SetMovingShadowBool(true);
			}

			m_KeyboardInterstate.at('V') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('V') = false;
	}

	if (m_KeyboardEvents->GetKeys().at('M'))
	{
		if (!m_KeyboardInterstate.at('M'))
		{
			if (m_Graphics->GetLightMarkerBool())
			{
				m_Graphics->SetLightMarkerBool(false);
			}
			else
			{
				m_Graphics->SetLightMarkerBool(true);
			}

			m_KeyboardInterstate.at('M') = true;
		}
	}
	else
	{
		m_KeyboardInterstate.at('M') = false;
	}
}

LRESULT CALLBACK Scene::ProgramCallBack(const HWND hwnd, const UINT uMessage, const WPARAM wparam, const LPARAM lparam)
{
	switch (uMessage)
	{
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		m_KeyboardEvents->KeyDown(static_cast<int>(wparam));

		return 0;
	}

	// Check if a key has been released on the keyboard.
	case WM_KEYUP:
	{
		// If a key is released then send it to the input object so it can unset the state for that key.
		m_KeyboardEvents->KeyUp(static_cast<int>(wparam));

		return 0;
	}

	// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, uMessage, wparam, lparam);
	}
	}

	return 0;
}

LRESULT CALLBACK WindowsCallBack(const HWND hwnd, const UINT uMessage, const WPARAM wparam, const LPARAM lparam)
{
	switch (uMessage)
	{
		// Check if the window is being destroyed or closed.
	case WM_DESTROY:
	case WM_CLOSE:
	{
		PostQuitMessage(0);

		return 0;
	}

	// All other messages pass to the message handler in the scene.
	default:
	{
		return This->ProgramCallBack(hwnd, uMessage, wparam, lparam);
	}
	}

	return 0;
}