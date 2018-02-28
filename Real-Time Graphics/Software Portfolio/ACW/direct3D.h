#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include <array>

using namespace std;
using namespace DirectX;

class Direct3D
{
public:
	Direct3D();
	Direct3D(const HWND, const XMFLOAT2 &, const XMFLOAT2 &);
	Direct3D(const Direct3D &);
	Direct3D & operator = (const Direct3D &);
	Direct3D(const Direct3D &&);
	Direct3D & operator = (const Direct3D &&);
	~Direct3D();

	IDXGISwapChain * GetSwapChain() const
	{
		return m_SwapChain;
	}

	ID3D11Device * GetDevice() const
	{
		return m_Device;
	}

	ID3D11DeviceContext * GetDeviceContext() const
	{
		return m_DeviceContext;
	}

	ID3D11RenderTargetView * GetRenderTargetView() const
	{
		return m_RenderTargetView;
	}

	ID3D11Texture2D * GetDepthStencilBuffer() const
	{
		return m_DepthStencilBuffer;
	}

	ID3D11DepthStencilState * GetDepthStencilState() const
	{
		return m_DepthStencilState;
	}

	ID3D11DepthStencilState * GetDisabledDepthStencilState() const
	{
		return m_DisabledDepthStencilState;
	}

	ID3D11DepthStencilView * GetDepthStencilView() const
	{
		return m_DepthStencilView;
	}

	ID3D11BlendState * GetEnableAlphaBlendState() const
	{
		return m_EnableAlphaBlendState;
	}

	ID3D11BlendState * GetDisableAlphaBlendState() const
	{
		return m_DisableAlphaBlendState;
	}

	ID3D11RasterizerState * GetSolidRasteriserState() const
	{
		return m_SolidRasteriserState;
	}

	ID3D11RasterizerState * GetWireframeRasteriserState() const
	{
		return m_WireframeRasteriserState;
	}

	const XMMATRIX & GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const XMMATRIX & GetWorldMatrix() const
	{
		return m_WorldMatrix;
	}

	const XMMATRIX & GetOrthographicMatrix() const
	{
		return m_OrthographicMatrix;
	}

	const XMFLOAT2 & GetScreen() const
	{
		return m_Screen;
	}

	const array<char, 75> & GetVideoCardDescription() const
	{
		return m_VideoCardDescription;
	}

	const int GetVideoCardMemory() const
	{
		return m_VideoCardMemory;
	}

	void SetSwapChain(IDXGISwapChain * const swapChain)
	{
		m_SwapChain = swapChain;
	}

	void SetDevice(ID3D11Device * const device)
	{
		m_Device = device;
	}

	void SetDeviceContext(ID3D11DeviceContext * const deviceContext)
	{
		m_DeviceContext = deviceContext;
	}

	void SetRenderTargetView(ID3D11RenderTargetView * const renderTargetView)
	{
		m_RenderTargetView = renderTargetView;
	}

	void SetDepthStencilBuffer(ID3D11Texture2D * const depthStencilBuffer)
	{
		m_DepthStencilBuffer = depthStencilBuffer;
	}

	void SetDepthStencilState(ID3D11DepthStencilState * const depthStencilState)
	{
		m_DepthStencilState = depthStencilState;
	}

	void SetDisabledDepthStencilState(ID3D11DepthStencilState * const disabledDepthStencilState)
	{
		m_DisabledDepthStencilState = disabledDepthStencilState;
	}

	void SetDepthStencilView(ID3D11DepthStencilView * const depthStencilView)
	{
		m_DepthStencilView = depthStencilView;
	}

	void SetEnableAlphaBlendState(ID3D11BlendState * const enableAlphaBlendState)
	{
		m_EnableAlphaBlendState = enableAlphaBlendState;
	}

	void SetDisableAlphaBlendState(ID3D11BlendState * const disableAlphaBlendState)
	{
		m_DisableAlphaBlendState = disableAlphaBlendState;
	}

	void SetSolidRasteriserState(ID3D11RasterizerState * const solidRasteriserState)
	{
		m_SolidRasteriserState = solidRasteriserState;
	}

	void SetWireframeRasteriserState(ID3D11RasterizerState * const wireframeRasteriserState)
	{
		m_WireframeRasteriserState = wireframeRasteriserState;
	}

	void SetProjectionMatrix(const XMMATRIX &projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;
	}

	void SetWorldMatrix(const XMMATRIX &worldMatrix)
	{
		m_WorldMatrix = worldMatrix;
	}

	void SetOrthographicMatrix(const XMMATRIX &orthographicMatrix)
	{
		m_OrthographicMatrix = orthographicMatrix;
	}

	void SetScreen(const XMFLOAT2 &screen)
	{
		m_Screen = screen;
	}

	void SetVideoCardDescription(const array<char, 75> &videoCardDescription)
	{
		m_VideoCardDescription = videoCardDescription;
	}

	void SetVideoCardMemory(const int videoCardMemory)
	{
		m_VideoCardMemory = videoCardMemory;
	}

	void BeginScene(const float, const float, const float, const float);

	void EndScene()
	{
		// Present the back buffer to the screen since rendering is complete.
		m_SwapChain->Present(1, 0);
	}

private:
	IDXGISwapChain *m_SwapChain;
	ID3D11Device *m_Device;
	ID3D11DeviceContext *m_DeviceContext;
	ID3D11RenderTargetView *m_RenderTargetView;
	ID3D11Texture2D *m_DepthStencilBuffer;
	ID3D11DepthStencilState *m_DepthStencilState;
	ID3D11DepthStencilState *m_DisabledDepthStencilState;
	ID3D11DepthStencilView *m_DepthStencilView;
	ID3D11BlendState *m_EnableAlphaBlendState;
	ID3D11BlendState *m_DisableAlphaBlendState;
	ID3D11RasterizerState *m_SolidRasteriserState;
	ID3D11RasterizerState *m_WireframeRasteriserState;
	XMMATRIX m_ProjectionMatrix, m_WorldMatrix, m_OrthographicMatrix;
	XMFLOAT2 m_Screen;
	array<char, 75> m_VideoCardDescription;
	int m_VideoCardMemory;
};