#pragma once

#include <directxmath.h>
#include <array>
#include <vector>
#include <random>
#include "direct3D.h"
#include "view.h"
#include "modelLoader.h"
#include "modelShader.h"
#include "shadowShader.h"
#include "image.h"
#include "model.h"
#include "light.h"
#include "graphicsLoader.h"
#include "particles.h"

using namespace std;
using namespace DirectX;

class Graphics
{
public:
	Graphics();
	Graphics(const HWND, const XMFLOAT2 &, const XMFLOAT2 &);
	Graphics(const HWND, const XMFLOAT2 &, const XMFLOAT2 &, GraphicsLoader *);
	Graphics(const Graphics &);
	Graphics & operator = (const Graphics &);
	Graphics(const Graphics &&);
	Graphics & operator = (const Graphics &&);
	~Graphics();

	const Direct3D * GetDirect3D() const
	{
		return m_Direct3D;
	}

	const View * GetView() const
	{
		return m_View;
	}

	const ModelShader * GetModelShader() const
	{
		return m_ModelShader;
	}

	const ShadowShader * GetShadowShader() const
	{
		return m_ShadowShader;
	}

	const Image * GetImage() const
	{
		return m_Image;
	}

	const vector<Model *>  & GetModels() const
	{
		return m_Models;
	}

	const Light * GetLight() const
	{
		return m_Light;
	}

	const vector<XMFLOAT3 *> & GetPath() const
	{
		return m_Path;
	}

	const Particles * GetParticles() const
	{
		return m_Particles;
	}
	
	const bool GetPauseBool() const
	{
		return m_PauseBool;
	}

	const bool GetTimeOffsetBool() const
	{
		return m_TimeOffsetBool;
	}

	const bool GetTrackingViewBool() const
	{
		return m_TrackingViewBool;
	}

	const bool GetViewPositionBool() const
	{
		return m_ViewPositionBool;
	}

	const bool GetViewEyePositionBool() const
	{
		return m_ViewEyePositionBool;
	}

	const bool GetUpdateBool() const
	{
		return m_UpdateBool;
	}

	const bool GetMoveBool() const
	{
		return m_MoveBool;
	}

	const bool GetKeyStateBool() const
	{
		return m_KeyStateBool;
	}

	const bool GetHUDBool() const
	{
		return m_HUDBool;
	}

	const bool GetEyeBool() const
	{
		return m_EyeBool;
	}

	const bool GetStickShadowBool() const
	{
		return m_StickShadowBool;
	}

	const bool GetMultipleShadowBool() const
	{
		return m_MultipleShadowBool;
	}

	const bool GetMovingShadowBool() const
	{
		return m_MovingShadowBool;
	}

	const bool GetLightMarkerBool() const
	{
		return m_LightMarkerBool;
	}

	const float GetTimeElapsed() const
	{
		return m_TimeElapsed;
	}

	const float GetTimeOffset() const
	{
		return m_TimeOffset;
	}

	const float GetObjectState() const
	{
		return m_ObjectState;
	}

	const int GetUpdateCount() const
	{
		return m_UpdateCount;
	}

	const float GetRenderState() const
	{
		return m_RenderState;
	}

	void SetDirect3D(Direct3D * const direct3D)
	{
		m_Direct3D = direct3D;
	}

	void SetView(View * const view)
	{
		m_View = view;
	}

	void SetModelShader(ModelShader * const modelShader)
	{
		m_ModelShader = modelShader;
	}

	void SetShadowShader(ShadowShader * const shadowShader)
	{
		m_ShadowShader = shadowShader;
	}

	void SetImage(Image * const image)
	{
		m_Image = image;
	}

	void SetModels(const vector<Model *>  &models)
	{
		m_Models = models;
	}

	void SetLight(Light * const light)
	{
		m_Light = light;
	}

	void SetPath(const vector<XMFLOAT3 *> &path)
	{
		m_Path = path;
	}

	void SetParticles(Particles * const particles)
	{
		m_Particles = particles;
	}

	void SetPauseBool(const bool pauseBool)
	{
		m_PauseBool = pauseBool;
	}

	void SetTimeOffsetBool(const bool timeOffsetBool)
	{
		m_TimeOffsetBool = timeOffsetBool;
	}

	void SetTrackingViewBool(const bool trackingViewBool)
	{
		m_TrackingViewBool = trackingViewBool;
	}

	void SetViewPositionBool(const bool viewPositionBool)
	{
		m_ViewPositionBool = viewPositionBool;
	}

	void SetViewEyePositionBool(const bool viewEyePositionBool)
	{
		m_ViewEyePositionBool = viewEyePositionBool;
	}

	void SetUpdateBool(const bool updateBool)
	{
		m_UpdateBool = updateBool;
	}

	void SetMoveBool(const bool moveBool)
	{
		m_MoveBool = moveBool;
	}

	void SetKeyStateBool(const bool keyStateBool)
	{
		m_KeyStateBool = keyStateBool;
	}

	void SetHUDBool(const bool hudBool)
	{
		m_HUDBool = hudBool;
	}

	void SetEyeBool(const bool eyeBool)
	{
		m_EyeBool = eyeBool;
	}

	void SetStickShadowBool(const bool stickShadowBool)
	{
		m_StickShadowBool = stickShadowBool;
	}

	void SetMultipleShadowBool(const bool multipleShadowBool)
	{
		m_MultipleShadowBool = multipleShadowBool;
	}

	void SetMovingShadowBool(const bool movingShadowBool)
	{
		m_MovingShadowBool = movingShadowBool;
	}

	void SetLightMarkerBool(const bool lightMarkerBool)
	{
		m_LightMarkerBool = lightMarkerBool;
	}

	void SetTimeElapsed(const float timeElapsed)
	{
		m_TimeElapsed = timeElapsed;
	}

	void SetTimeOffset(const float timeOffset)
	{
		m_TimeOffset = timeOffset;
	}

	void SetObjectState(const float objectState)
	{
		m_ObjectState = objectState;
	}

	void SetUpdateCount(const int updateCount)
	{
		m_UpdateCount = updateCount;
	}

	void SetRenderState(const float renderState)
	{
		m_RenderState = renderState;
	}

	bool Update(const int, const int, const float, const float);
	bool Render();

private:
	Direct3D *m_Direct3D;
	View *m_View;
	ModelShader *m_ModelShader;
	ShadowShader *m_ShadowShader;
	Image *m_Image;
	vector<Model *> m_Models;
	Light *m_Light;
	vector<XMFLOAT3 *> m_Path;
	Particles *m_Particles;
	bool m_PauseBool, m_TimeOffsetBool, m_TrackingViewBool, m_ViewPositionBool, m_ViewEyePositionBool, m_UpdateBool, m_MoveBool, m_KeyStateBool, m_HUDBool, m_EyeBool, m_StickShadowBool, m_MultipleShadowBool, m_MovingShadowBool, m_LightMarkerBool;
	int m_UpdateCount;
	float m_TimeElapsed, m_TimeOffset, m_ObjectState, m_RenderState;
};