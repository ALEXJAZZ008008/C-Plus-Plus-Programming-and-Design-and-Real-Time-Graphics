#include "direct3D.h"

Direct3D::Direct3D() : m_SwapChain(nullptr), m_Device(nullptr), m_DeviceContext(nullptr), m_RenderTargetView(nullptr), m_DepthStencilBuffer(nullptr), m_DepthStencilState(nullptr), m_DisabledDepthStencilState(nullptr), m_DepthStencilView(nullptr), m_EnableAlphaBlendState(nullptr), m_DisableAlphaBlendState(nullptr), m_SolidRasteriserState(nullptr), m_WireframeRasteriserState(nullptr), m_ProjectionMatrix(), m_WorldMatrix(), m_OrthographicMatrix(), m_Screen(), m_VideoCardDescription(), m_VideoCardMemory(0)
{
	
}

Direct3D::Direct3D(const HWND hwnd, const XMFLOAT2 &screen, const XMFLOAT2 &clip) : m_SwapChain(nullptr), m_Device(nullptr), m_DeviceContext(nullptr), m_RenderTargetView(nullptr), m_DepthStencilBuffer(nullptr), m_DepthStencilState(nullptr), m_DisabledDepthStencilState(nullptr), m_DepthStencilView(nullptr), m_EnableAlphaBlendState(nullptr), m_DisableAlphaBlendState(nullptr), m_SolidRasteriserState(nullptr), m_WireframeRasteriserState(nullptr), m_ProjectionMatrix(), m_WorldMatrix(XMMatrixIdentity()), m_OrthographicMatrix(XMMatrixOrthographicLH(static_cast<float>(screen.x), static_cast<float>(screen.y), static_cast<float>(clip.y), static_cast<float>(clip.x))), m_Screen(screen), m_VideoCardDescription(), m_VideoCardMemory(0)
{
	IDXGIFactory *factory = nullptr;

	// Create a DirectX graphics interface factory.
	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&factory));

	IDXGIAdapter *adapter = nullptr;

	// Use the factory to create an adapter for the primary graphics interface (video card).
	factory->EnumAdapters(0, &adapter);

	IDXGIOutput *adapterOutput = nullptr;

	// Enumerate the primary adapter output (monitor).
	adapter->EnumOutputs(0, &adapterOutput);

	unsigned int numberOfModes = 0;

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numberOfModes, nullptr);

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	DXGI_MODE_DESC * const displayModeList = new DXGI_MODE_DESC[numberOfModes];

	// Now fill the display mode list structures.
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numberOfModes, displayModeList);

	int numerator = 0;
	int denominator = 0;

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (unsigned int i = 0; i < numberOfModes; i++)
	{
		if (displayModeList[i].Width == static_cast<int>(screen.x))
		{
			if (displayModeList[i].Height == static_cast<int>(screen.y))
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapterDesc =
	{
		sizeof(adapterDesc)
	};

	// Get the adapter (video card) description.
	adapter->GetDesc(&adapterDesc);

	// Store the dedicated video card memory in megabytes.
	m_VideoCardMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1048576);

	unsigned long long stringLength = 0;

	// Convert the name of the video card to a character array and store it.
	wcstombs_s(&stringLength, m_VideoCardDescription.data(), m_VideoCardDescription.size(), adapterDesc.Description, m_VideoCardDescription.size());

	// Release the display mode list.
	delete[] displayModeList;

	// Release the adapter output.
	adapterOutput->Release();

	// Release the adapter.
	adapter->Release();

	// Release the factory.
	factory->Release();

	DXGI_SWAP_CHAIN_DESC swapChainDesc =
	{
		sizeof(swapChainDesc)
	};

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = static_cast<unsigned int>(screen.x);
	swapChainDesc.BufferDesc.Height = static_cast<unsigned int>(screen.y);

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = hwnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	swapChainDesc.Windowed = false;

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	int deviceFlags = 0;

#ifdef _DEBUG
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Set the feature level to DirectX 11.
	array<D3D_FEATURE_LEVEL, 4> featureLevel =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	// Create the swap chain, Direct3D device, and Direct3D device context.
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, featureLevel.data(), static_cast<int>(featureLevel.size()), D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, nullptr, &m_DeviceContext);

	ID3D11Texture2D *backBufferPtr = nullptr;

	// Get the pointer to the back buffer.
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID *>(&backBufferPtr));

	// Create the render target view with the back buffer pointer.
	m_Device->CreateRenderTargetView(backBufferPtr, nullptr, &m_RenderTargetView);

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();

	D3D11_TEXTURE2D_DESC depthBufferDesc =
	{
		sizeof(depthBufferDesc)
	};

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = static_cast<unsigned int>(screen.x);
	depthBufferDesc.Height = static_cast<unsigned int>(screen.y);
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	m_Device->CreateTexture2D(&depthBufferDesc, nullptr, &m_DepthStencilBuffer);

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc =
	{
		sizeof(depthStencilDesc)
	};

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);

	// Set the depth stencil state.
	m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1);

	D3D11_DEPTH_STENCIL_DESC disabledDepthStencilDesc =
	{
		sizeof(disabledDepthStencilDesc)
	};

	// Set up the description of the stencil state.
	disabledDepthStencilDesc.DepthEnable = false;
	disabledDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	disabledDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	disabledDepthStencilDesc.StencilEnable = true;
	disabledDepthStencilDesc.StencilReadMask = 0xFF;
	disabledDepthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	disabledDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	disabledDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	disabledDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	disabledDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	disabledDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	disabledDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	disabledDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	disabledDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	m_Device->CreateDepthStencilState(&disabledDepthStencilDesc, &m_DisabledDepthStencilState);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc =
	{

	};

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	m_Device->CreateDepthStencilView(m_DepthStencilBuffer, &depthStencilViewDesc, &m_DepthStencilView);

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	D3D11_BLEND_DESC blendDesc =
	{
		sizeof(blendDesc)
	};

	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	m_Device->CreateBlendState(&blendDesc, &m_EnableAlphaBlendState);

	blendDesc.RenderTarget[0].BlendEnable = FALSE;

	m_Device->CreateBlendState(&blendDesc, &m_DisableAlphaBlendState);

	D3D11_RASTERIZER_DESC rasterDesc =
	{

	};

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = true;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = false;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = true;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	m_Device->CreateRasterizerState(&rasterDesc, &m_SolidRasteriserState);

	// Now set the rasterizer state.
	m_DeviceContext->RSSetState(m_SolidRasteriserState);

	rasterDesc.FillMode = D3D11_FILL_WIREFRAME;

	m_Device->CreateRasterizerState(&rasterDesc, &m_WireframeRasteriserState);

	D3D11_VIEWPORT viewport =
	{
		sizeof(viewport)
	};

	// Setup the viewport for rendering.
	viewport.Width = static_cast<float>(screen.x);
	viewport.Height = static_cast<float>(screen.y);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	m_DeviceContext->RSSetViewports(1, &viewport);

	// Setup the projection matrix.
	const float fieldOfView = 3.141592653589793238462643383279502884f / 4.0f;
	const float screenAspect = static_cast<float>(screen.x) / static_cast<float>(screen.y);

	// Create the projection matrix for 3D rendering.
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(static_cast<float>(fieldOfView), static_cast<float>(screenAspect), static_cast<float>(clip.y), static_cast<float>(clip.x));
}

Direct3D::Direct3D(const Direct3D &direct3D) : m_SwapChain(direct3D.GetSwapChain()), m_Device(direct3D.GetDevice()), m_DeviceContext(direct3D.GetDeviceContext()), m_RenderTargetView(direct3D.GetRenderTargetView()), m_DepthStencilBuffer(direct3D.GetDepthStencilBuffer()), m_DepthStencilState(direct3D.GetDepthStencilState()), m_DisabledDepthStencilState(direct3D.GetDisabledDepthStencilState()), m_DepthStencilView(direct3D.GetDepthStencilView()), m_EnableAlphaBlendState(direct3D.GetEnableAlphaBlendState()), m_DisableAlphaBlendState(direct3D.GetDisableAlphaBlendState()), m_SolidRasteriserState(direct3D.GetSolidRasteriserState()), m_WireframeRasteriserState(direct3D.GetWireframeRasteriserState()), m_ProjectionMatrix(direct3D.GetProjectionMatrix()), m_WorldMatrix(direct3D.GetWorldMatrix()), m_OrthographicMatrix(direct3D.GetOrthographicMatrix()), m_Screen(direct3D.GetScreen()), m_VideoCardDescription(direct3D.GetVideoCardDescription()), m_VideoCardMemory(direct3D.GetVideoCardMemory())
{
	
}

Direct3D & Direct3D::operator = (const Direct3D &direct3D)
{
	if (this != &direct3D)
	{
		m_SwapChain = direct3D.GetSwapChain();
		m_Device = direct3D.GetDevice();
		m_DeviceContext = direct3D.GetDeviceContext();
		m_RenderTargetView = direct3D.GetRenderTargetView();
		m_DepthStencilBuffer = direct3D.GetDepthStencilBuffer();
		m_DepthStencilState = direct3D.GetDepthStencilState();
		m_DisabledDepthStencilState = direct3D.GetDisabledDepthStencilState();
		m_DepthStencilView = direct3D.GetDepthStencilView();
		m_EnableAlphaBlendState = direct3D.GetEnableAlphaBlendState();
		m_DisableAlphaBlendState = direct3D.GetDisableAlphaBlendState();
		m_SolidRasteriserState = direct3D.GetSolidRasteriserState();
		m_WireframeRasteriserState = direct3D.GetWireframeRasteriserState();

		m_ProjectionMatrix = direct3D.GetProjectionMatrix();
		m_WorldMatrix = direct3D.GetWorldMatrix();
		m_OrthographicMatrix = direct3D.GetOrthographicMatrix();

		m_Screen = direct3D.GetScreen();

		m_VideoCardDescription = direct3D.GetVideoCardDescription();
		m_VideoCardMemory = direct3D.GetVideoCardMemory();
	}

	return *this;
}

Direct3D::Direct3D(const Direct3D &&direct3D) : m_SwapChain(direct3D.GetSwapChain()), m_Device(direct3D.GetDevice()), m_DeviceContext(direct3D.GetDeviceContext()), m_RenderTargetView(direct3D.GetRenderTargetView()), m_DepthStencilBuffer(direct3D.GetDepthStencilBuffer()), m_DepthStencilState(direct3D.GetDepthStencilState()), m_DisabledDepthStencilState(direct3D.GetDisabledDepthStencilState()), m_DepthStencilView(direct3D.GetDepthStencilView()), m_EnableAlphaBlendState(direct3D.GetEnableAlphaBlendState()), m_DisableAlphaBlendState(direct3D.GetDisableAlphaBlendState()), m_SolidRasteriserState(direct3D.GetSolidRasteriserState()), m_WireframeRasteriserState(direct3D.GetWireframeRasteriserState()), m_ProjectionMatrix(direct3D.GetProjectionMatrix()), m_WorldMatrix(direct3D.GetWorldMatrix()), m_OrthographicMatrix(direct3D.GetOrthographicMatrix()), m_Screen(direct3D.GetScreen()), m_VideoCardDescription(direct3D.GetVideoCardDescription()), m_VideoCardMemory(direct3D.GetVideoCardMemory())
{

}

Direct3D & Direct3D::operator = (const Direct3D &&direct3D)
{
	if (this != &direct3D)
	{
		m_SwapChain = direct3D.GetSwapChain();
		m_Device = direct3D.GetDevice();
		m_DeviceContext = direct3D.GetDeviceContext();
		m_RenderTargetView = direct3D.GetRenderTargetView();
		m_DepthStencilBuffer = direct3D.GetDepthStencilBuffer();
		m_DepthStencilState = direct3D.GetDepthStencilState();
		m_DisabledDepthStencilState = direct3D.GetDisabledDepthStencilState();
		m_DepthStencilView = direct3D.GetDepthStencilView();
		m_EnableAlphaBlendState = direct3D.GetEnableAlphaBlendState();
		m_DisableAlphaBlendState = direct3D.GetDisableAlphaBlendState();
		m_SolidRasteriserState = direct3D.GetSolidRasteriserState();
		m_WireframeRasteriserState = direct3D.GetWireframeRasteriserState();

		m_ProjectionMatrix = direct3D.GetProjectionMatrix();
		m_WorldMatrix = direct3D.GetWorldMatrix();
		m_OrthographicMatrix = direct3D.GetOrthographicMatrix();

		m_Screen = direct3D.GetScreen();

		m_VideoCardDescription = direct3D.GetVideoCardDescription();
		m_VideoCardMemory = direct3D.GetVideoCardMemory();
	}

	return *this;
}

Direct3D::~Direct3D()
{
	try
	{
		m_SolidRasteriserState->Release();
		m_WireframeRasteriserState->Release();

		m_EnableAlphaBlendState->Release();

		m_DisableAlphaBlendState->Release();

		m_DepthStencilView->Release();

		m_DepthStencilState->Release();

		m_DisabledDepthStencilState->Release();

		m_DepthStencilBuffer->Release();

		m_RenderTargetView->Release();

		m_DeviceContext->Release();

		m_Device->Release();

		m_SwapChain->Release();
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void Direct3D::BeginScene(const float red, const float green, const float blue, const float alpha)
{
	// Setup the color to clear the buffer to.
	array<float, 4> colour =
	{
		red,
		green,
		blue,
		alpha
	};

	// Clear the back buffer.
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, colour.data());

	// Clear the depth buffer.
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}