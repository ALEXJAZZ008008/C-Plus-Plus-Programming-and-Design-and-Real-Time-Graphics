#include "graphics.h"

Graphics::Graphics() : m_Direct3D(nullptr), m_View(nullptr), m_ModelShader(nullptr), m_ShadowShader(nullptr), m_Image(nullptr), m_Models(), m_Light(nullptr), m_Path(), m_Particles(nullptr), m_PauseBool(false), m_TimeOffsetBool(false), m_TrackingViewBool(false), m_ViewPositionBool(false), m_ViewEyePositionBool(false), m_UpdateBool(false), m_MoveBool(false), m_KeyStateBool(false), m_HUDBool(false), m_EyeBool(false), m_StickShadowBool(false), m_MultipleShadowBool(false), m_MovingShadowBool(false), m_LightMarkerBool(false), m_UpdateCount(0), m_TimeElapsed(0.0f), m_TimeOffset(0.0f), m_ObjectState(0.0f), m_RenderState(0.0f)
{
	
}

Graphics::Graphics(const HWND hwnd, const XMFLOAT2 &screen, const XMFLOAT2 &clip) : m_Direct3D(new Direct3D(hwnd, screen, clip)), m_View(new View(XMFLOAT3(0.0f, 1.0f, -13.0f), XMFLOAT3(0.0f, 1.0f, -4.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f))), m_ModelShader(nullptr), m_ShadowShader(nullptr), m_Image(nullptr), m_Models(), m_Light(new Light[3]), m_Path(), m_Particles(nullptr), m_PauseBool(false), m_TimeOffsetBool(false), m_TrackingViewBool(false), m_ViewPositionBool(false), m_ViewEyePositionBool(false), m_UpdateBool(false), m_MoveBool(false), m_KeyStateBool(false), m_HUDBool(false), m_EyeBool(false), m_StickShadowBool(false), m_MultipleShadowBool(false), m_MovingShadowBool(false), m_LightMarkerBool(false), m_UpdateCount(0), m_TimeElapsed(0.0f), m_TimeOffset(0.0f), m_ObjectState(0.0f), m_RenderState(0.0f)
{
	// Set the initial position of the camera.
	m_View->SetViewToOutside();
	m_View->Render();

	m_ModelShader = new ModelShader(m_Direct3D->GetDevice());

	m_ShadowShader = new ShadowShader(m_Direct3D->GetDevice());

	m_Image = new Image(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screen, m_View->GetViewMatrix(), "../ACW/models/text/textMap.txt", "../ACW/models/text/textTexture.tga");

	ModelLoader *modelLoader = new ModelLoader();

	// Create and initialise the model object.
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/dragonfly/body/body/dragonflyBodyMesh.obj", "../ACW/models/dragonfly/body/body/dragonflyBodyTexture.tga", "../ACW/models/dragonfly/body/body/dragonflyBodyBumpMap.tga", "../ACW/models/dragonfly/body/body/dragonflyBodySpecularMap.tga", XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(-0.05f, 0.7f, -0.02f), XMFLOAT3(15.0f, 270.0f, 0.0f), 1.0f, 32.0f, 1.0f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/dragonfly/body/eyes/dragonflyBodyEyesMesh.obj", "../ACW/models/dragonfly/body/eyes/dragonflyBodyEyesTexture.tga", "../ACW/models/dragonfly/body/eyes/dragonflyBodyEyesBumpMap.tga", "../ACW/models/dragonfly/body/eyes/dragonflyBodyEyesSpecularMap.tga", XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.55f, 0.35f, 0.45f), XMFLOAT3(-0.07f, 0.75f, -0.02f), XMFLOAT3(15.0f, 270.0f, 0.0f), 2.0f, 32.0f, 1.0f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/dragonfly/wings/dragonflyWingsMesh.obj", "../ACW/models/dragonfly/wings/dragonflyWingsTexture.tga", "../ACW/models/dragonfly/wings/dragonflyWingsBumpMap.tga", "../ACW/models/dragonfly/wings/dragonflyWingsSpecularMap.tga", XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(-0.05f, 0.7f, -0.02f), XMFLOAT3(15.0f, 270.0f, 0.0f), 3.0f, 64.0f, 0.75f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/stick/stickMesh.obj", "../ACW/models/stick/stickTexture.tga", "../ACW/models/stick/stickBumpMap.tga", "../ACW/models/stick/stickSpecularMap.tga", XMFLOAT4(0.5f, 0.2f, 0.1f, 1.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 4.0f, 16.0f, 1.0f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/desert/desertMesh.obj", "../ACW/models/desert/desertTexture.tga", "../ACW/models/desert/desertBumpMap.tga", "../ACW/models/desert/desertSpecularMap.tga", XMFLOAT4(0.9f, 0.7f, 0.5f, 1.0f), XMFLOAT3(8.0f, 8.0f, 8.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 5.0f, 16.0f, 1.0f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/hemisphere/hemisphereMesh.obj", "../ACW/models/hemisphere/hemisphereTexture.tga", "../ACW/models/hemisphere/hemisphereBumpMap.tga", "../ACW/models/hemisphere/hemisphereSpecularMap.tga", XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(270.0f, 0.0f, 0.0f), 6.0f, 4.0f, 0.6f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/cube/cubeMesh.obj", "../ACW/models/cube/cubeTexture.tga", "../ACW/models/cube/cubeBumpMap.tga", "../ACW/models/cube/cubeSpecularMap.tga", XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 7.0f, 32.0f, 1.0f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/hemisphere/hemisphereMesh.obj", "../ACW/models/hemisphere/hemisphereTexture.tga", "../ACW/models/hemisphere/hemisphereBumpMap.tga", "../ACW/models/hemisphere/hemisphereSpecularMap.tga", XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT3(10.0f, 10.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 8.0f, 4.0f, 0.6f));

	m_Light[0].SetPosition(0.0f, 4.0f, -2.0f, 1.0f);
	m_Light[0].SetAmbientColour(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light[0].SetDiffuseColour(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light[0].SetSpecularColour(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light[0].SetPathAt(XMFLOAT3(0.0f, 4.0f, -2.0f), 0);
	m_Light[0].SetPathAt(XMFLOAT3(0.0f, 4.0f, -2.0f), 1);
	m_Light[0].SetPathAt(XMFLOAT3(0.0f, 4.0f, -2.0f), 2);

	m_Light[1].SetPosition(0.0f, 4.0f, 1.0f, 1.0f);
	m_Light[1].SetAmbientColour(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light[1].SetDiffuseColour(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light[1].SetSpecularColour(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light[1].SetPathAt(XMFLOAT3(0.0f, 4.0f, 1.0f), 0);
	m_Light[1].SetPathAt(XMFLOAT3(0.0f, 4.0f, 1.0f), 1);
	m_Light[1].SetPathAt(XMFLOAT3(0.0f, 4.0f, 1.0f), 2);

	m_Light[2].SetPosition(0.0f, 2.0f, -1.0f, 1.0f);
	m_Light[2].SetAmbientColour(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light[2].SetDiffuseColour(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light[2].SetSpecularColour(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light[2].SetPathAt(XMFLOAT3(-2.0f, 4.0f, 2.0f), 0);
	m_Light[2].SetPathAt(XMFLOAT3(0.0f, 2.0f, -1.0f), 1);
	m_Light[2].SetPathAt(XMFLOAT3(2.0f, 4.0f, 2.0f), 2);

	random_device randomDevice;
	mt19937 mt(randomDevice());
	const uniform_real_distribution<float> random(-6.0f, 6.0f);

	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));
	m_Path.push_back(new XMFLOAT3(random(mt), random(mt), random(mt)));

	m_Particles = new Particles(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ACW/models/particle/particleTexture.tga");
}

Graphics::Graphics(const HWND hwnd, const XMFLOAT2 &screen, const XMFLOAT2 &clip, GraphicsLoader *graphicsLoader) : m_Direct3D(new Direct3D(hwnd, screen, clip)), m_View(new View(XMFLOAT3(graphicsLoader->GetView()->GetOutsidePositionX(), graphicsLoader->GetView()->GetOutsidePositionY(), graphicsLoader->GetView()->GetOutsidePositionZ()), XMFLOAT3(graphicsLoader->GetView()->GetInsidePositionX(), graphicsLoader->GetView()->GetInsidePositionY(), graphicsLoader->GetView()->GetInsidePositionZ()), XMFLOAT3(graphicsLoader->GetView()->GetOutsideRotationX(), graphicsLoader->GetView()->GetOutsideRotationY(), graphicsLoader->GetView()->GetOutsideRotationZ()), XMFLOAT3(graphicsLoader->GetView()->GetInsideRotationX(), graphicsLoader->GetView()->GetInsideRotationY(), graphicsLoader->GetView()->GetInsideRotationZ()))), m_ModelShader(nullptr), m_ShadowShader(nullptr), m_Image(nullptr), m_Models(), m_Light(new Light[3]), m_Path(), m_Particles(nullptr), m_PauseBool(false), m_TimeOffsetBool(false), m_TrackingViewBool(false), m_ViewPositionBool(false), m_ViewEyePositionBool(false), m_UpdateBool(false), m_MoveBool(false), m_KeyStateBool(false), m_HUDBool(false), m_EyeBool(false), m_StickShadowBool(false), m_MultipleShadowBool(false), m_MovingShadowBool(false), m_LightMarkerBool(false), m_UpdateCount(0), m_TimeElapsed(0.0f), m_TimeOffset(0.0f), m_ObjectState(0.0f), m_RenderState(0.0f)
{
	// Set the initial position of the camera.
	m_View->SetViewToOutside();
	m_View->Render();

	m_ModelShader = new ModelShader(m_Direct3D->GetDevice());

	m_ShadowShader = new ShadowShader(m_Direct3D->GetDevice());

	m_Image = new Image(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screen, m_View->GetViewMatrix(), "../ACW/models/text/textMap.txt", "../ACW/models/text/textTexture.tga");

	ModelLoader *modelLoader = new ModelLoader();

	// Create and initialise the model object.
	for (int i = 0; i < 6; i++)
	{
		m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, graphicsLoader->GetModels().at(i)->GetModelFilename(), graphicsLoader->GetModels().at(i)->GetTextureFilename(), graphicsLoader->GetModels().at(i)->GetBumpMapFilename(), graphicsLoader->GetModels().at(i)->GetSpecularMapFilename(), graphicsLoader->GetModels().at(i)->GetColour(), graphicsLoader->GetModels().at(i)->GetSize(), graphicsLoader->GetModels().at(i)->GetPosition(), graphicsLoader->GetModels().at(i)->GetRotation(), i + 1.0f, graphicsLoader->GetModels().at(i)->GetReflectivity(), graphicsLoader->GetModels().at(i)->GetBlendAmount()));
	}

	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/cube/cubeMesh.obj", "../ACW/models/cube/cubeTexture.tga", "../ACW/models/cube/cubeBumpMap.tga", "../ACW/models/cube/cubeSpecularMap.tga", XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 7.0f, 32.0f, 1.0f));
	m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, "../ACW/models/hemisphere/hemisphereMesh.obj", "../ACW/models/hemisphere/hemisphereTexture.tga", "../ACW/models/hemisphere/hemisphereBumpMap.tga", "../ACW/models/hemisphere/hemisphereSpecularMap.tga", XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT3(25.0f, 25.0f, 25.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 8.0f, 4.0f, 0.6f));

	for (int i = 6; i < graphicsLoader->GetModels().size(); i++)
	{
		m_Models.push_back(new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelLoader, graphicsLoader->GetModels().at(i)->GetModelFilename(), graphicsLoader->GetModels().at(i)->GetTextureFilename(), graphicsLoader->GetModels().at(i)->GetBumpMapFilename(), graphicsLoader->GetModels().at(i)->GetSpecularMapFilename(), graphicsLoader->GetModels().at(i)->GetColour(), graphicsLoader->GetModels().at(i)->GetSize(), graphicsLoader->GetModels().at(i)->GetPosition(), graphicsLoader->GetModels().at(i)->GetRotation(), i + 1.0f, graphicsLoader->GetModels().at(i)->GetReflectivity(), graphicsLoader->GetModels().at(i)->GetBlendAmount()));
	}

	m_Light[0].SetPosition(graphicsLoader->GetLight()[0].GetPosition());
	m_Light[0].SetAmbientColour(graphicsLoader->GetLight()[0].GetAmbientColour());
	m_Light[0].SetDiffuseColour(graphicsLoader->GetLight()[0].GetDiffuseColour());
	m_Light[0].SetSpecularColour(graphicsLoader->GetLight()[0].GetSpecularColour());
	m_Light[0].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[0].GetPath().at(0)->x, graphicsLoader->GetLight()[0].GetPath().at(0)->y, graphicsLoader->GetLight()[0].GetPath().at(0)->z), 0);
	m_Light[0].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[0].GetPath().at(1)->x, graphicsLoader->GetLight()[0].GetPath().at(1)->y, graphicsLoader->GetLight()[0].GetPath().at(1)->z), 1);
	m_Light[0].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[0].GetPath().at(2)->x, graphicsLoader->GetLight()[0].GetPath().at(2)->y, graphicsLoader->GetLight()[0].GetPath().at(2)->z), 2);

	m_Light[1].SetPosition(graphicsLoader->GetLight()[1].GetPosition());
	m_Light[1].SetAmbientColour(graphicsLoader->GetLight()[1].GetAmbientColour());
	m_Light[1].SetDiffuseColour(graphicsLoader->GetLight()[1].GetDiffuseColour());
	m_Light[1].SetSpecularColour(graphicsLoader->GetLight()[1].GetSpecularColour());
	m_Light[1].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[1].GetPath().at(0)->x, graphicsLoader->GetLight()[1].GetPath().at(0)->y, graphicsLoader->GetLight()[1].GetPath().at(0)->z), 0);
	m_Light[1].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[1].GetPath().at(1)->x, graphicsLoader->GetLight()[1].GetPath().at(1)->y, graphicsLoader->GetLight()[1].GetPath().at(1)->z), 1);
	m_Light[1].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[1].GetPath().at(2)->x, graphicsLoader->GetLight()[1].GetPath().at(2)->y, graphicsLoader->GetLight()[1].GetPath().at(2)->z), 2);

	m_Light[2].SetPosition(graphicsLoader->GetLight()[2].GetPosition());
	m_Light[2].SetAmbientColour(graphicsLoader->GetLight()[2].GetAmbientColour());
	m_Light[2].SetDiffuseColour(graphicsLoader->GetLight()[2].GetDiffuseColour());
	m_Light[2].SetSpecularColour(graphicsLoader->GetLight()[2].GetSpecularColour());
	m_Light[2].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[2].GetPath().at(0)->x, graphicsLoader->GetLight()[2].GetPath().at(0)->y, graphicsLoader->GetLight()[2].GetPath().at(0)->z), 0);
	m_Light[2].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[2].GetPath().at(1)->x, graphicsLoader->GetLight()[2].GetPath().at(1)->y, graphicsLoader->GetLight()[2].GetPath().at(1)->z), 1);
	m_Light[2].SetPathAt(XMFLOAT3(graphicsLoader->GetLight()[2].GetPath().at(2)->x, graphicsLoader->GetLight()[2].GetPath().at(2)->y, graphicsLoader->GetLight()[2].GetPath().at(2)->z), 2);

	for (int i = 0; i < graphicsLoader->GetPath().size(); i++)
	{
		m_Path.push_back(new XMFLOAT3(graphicsLoader->GetPath().at(i)->x, graphicsLoader->GetPath().at(i)->y, graphicsLoader->GetPath().at(i)->z));
	}

	m_Particles = new Particles(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ACW/models/particle/particleTexture.tga");
}

Graphics::Graphics(const Graphics &graphics) : m_Direct3D(const_cast<Direct3D *>(graphics.GetDirect3D())), m_View(const_cast<View *>(graphics.GetView())), m_ModelShader(const_cast<ModelShader *>(graphics.GetModelShader())), m_ShadowShader(const_cast<ShadowShader *>(graphics.GetShadowShader())), m_Image(const_cast<Image *>(graphics.GetImage())), m_Models(graphics.GetModels()), m_Light(const_cast<Light *>(graphics.GetLight())), m_Path(graphics.GetPath()), m_Particles(const_cast<Particles *>(graphics.GetParticles())), m_PauseBool(graphics.GetPauseBool()), m_TimeOffsetBool(graphics.GetTimeOffsetBool()), m_TrackingViewBool(graphics.GetTrackingViewBool()), m_ViewPositionBool(graphics.GetViewPositionBool()), m_ViewEyePositionBool(graphics.GetViewEyePositionBool()), m_UpdateBool(graphics.GetUpdateBool()), m_MoveBool(graphics.GetMoveBool()), m_KeyStateBool(graphics.GetKeyStateBool()), m_HUDBool(graphics.GetHUDBool()), m_EyeBool(graphics.GetEyeBool()), m_StickShadowBool(graphics.GetStickShadowBool()), m_MultipleShadowBool(graphics.GetMultipleShadowBool()), m_MovingShadowBool(graphics.GetMovingShadowBool()), m_LightMarkerBool(graphics.GetLightMarkerBool()), m_UpdateCount(graphics.GetUpdateCount()), m_TimeElapsed(graphics.GetTimeElapsed()), m_TimeOffset(graphics.GetTimeOffset()), m_ObjectState(graphics.GetObjectState()), m_RenderState(graphics.GetRenderState())
{
	
}

Graphics & Graphics::operator = (const Graphics &graphics)
{
	if (this != &graphics)
	{
		m_Direct3D = const_cast<Direct3D *>(graphics.GetDirect3D());
		m_View = const_cast<View *>(graphics.GetView());
		m_ModelShader = const_cast<ModelShader *>(graphics.GetModelShader());
		m_ShadowShader = const_cast<ShadowShader *>(graphics.GetShadowShader());
		m_Image = const_cast<Image *>(graphics.GetImage());
		m_Models = graphics.GetModels();
		m_Light = const_cast<Light *>(graphics.GetLight());
		m_Path = graphics.GetPath();
		m_Particles = const_cast<Particles *>(graphics.GetParticles());

		m_PauseBool = graphics.GetPauseBool();
		m_TimeOffsetBool = graphics.GetTimeOffsetBool();
		m_TrackingViewBool = graphics.GetTrackingViewBool();
		m_ViewPositionBool = graphics.GetViewPositionBool();
		m_ViewEyePositionBool = graphics.GetViewEyePositionBool();
		m_UpdateBool = graphics.GetUpdateBool();
		m_MoveBool = graphics.GetMoveBool();
		m_KeyStateBool = graphics.GetKeyStateBool();
		m_HUDBool = graphics.GetHUDBool();
		m_EyeBool = graphics.GetEyeBool();
		m_StickShadowBool = graphics.GetStickShadowBool();
		m_MultipleShadowBool = graphics.GetMultipleShadowBool();
		m_MovingShadowBool = graphics.GetMovingShadowBool();
		m_LightMarkerBool = graphics.GetLightMarkerBool();

		m_TimeElapsed = graphics.GetTimeElapsed();
		m_TimeOffset = graphics.GetTimeOffset();
		m_ObjectState = graphics.GetObjectState();
		m_UpdateCount = graphics.GetUpdateCount();
		m_RenderState = graphics.GetRenderState();
	}

	return *this;
}

Graphics::Graphics(const Graphics &&graphics) : m_Direct3D(const_cast<Direct3D *>(graphics.GetDirect3D())), m_View(const_cast<View *>(graphics.GetView())), m_ModelShader(const_cast<ModelShader *>(graphics.GetModelShader())), m_ShadowShader(const_cast<ShadowShader *>(graphics.GetShadowShader())), m_Image(const_cast<Image *>(graphics.GetImage())), m_Models(graphics.GetModels()), m_Light(const_cast<Light *>(graphics.GetLight())), m_Path(graphics.GetPath()), m_Particles(const_cast<Particles *>(graphics.GetParticles())), m_PauseBool(graphics.GetPauseBool()), m_TimeOffsetBool(graphics.GetTimeOffsetBool()), m_TrackingViewBool(graphics.GetTrackingViewBool()), m_ViewPositionBool(graphics.GetViewPositionBool()), m_ViewEyePositionBool(graphics.GetViewEyePositionBool()), m_UpdateBool(graphics.GetUpdateBool()), m_MoveBool(graphics.GetMoveBool()), m_KeyStateBool(graphics.GetKeyStateBool()), m_HUDBool(graphics.GetHUDBool()), m_EyeBool(graphics.GetEyeBool()), m_StickShadowBool(graphics.GetStickShadowBool()), m_MultipleShadowBool(graphics.GetMultipleShadowBool()), m_MovingShadowBool(graphics.GetMovingShadowBool()), m_LightMarkerBool(graphics.GetLightMarkerBool()), m_UpdateCount(graphics.GetUpdateCount()), m_TimeElapsed(graphics.GetTimeElapsed()), m_TimeOffset(graphics.GetTimeOffset()), m_ObjectState(graphics.GetObjectState()), m_RenderState(graphics.GetRenderState())
{

}

Graphics & Graphics::operator = (const Graphics &&graphics)
{
	if (this != &graphics)
	{
		m_Direct3D = const_cast<Direct3D *>(graphics.GetDirect3D());
		m_View = const_cast<View *>(graphics.GetView());
		m_ModelShader = const_cast<ModelShader *>(graphics.GetModelShader());
		m_ShadowShader = const_cast<ShadowShader *>(graphics.GetShadowShader());
		m_Image = const_cast<Image *>(graphics.GetImage());
		m_Models = graphics.GetModels();
		m_Light = const_cast<Light *>(graphics.GetLight());
		m_Path = graphics.GetPath();
		m_Particles = const_cast<Particles *>(graphics.GetParticles());

		m_PauseBool = graphics.GetPauseBool();
		m_TimeOffsetBool = graphics.GetTimeOffsetBool();
		m_TrackingViewBool = graphics.GetTrackingViewBool();
		m_ViewPositionBool = graphics.GetViewPositionBool();
		m_ViewEyePositionBool = graphics.GetViewEyePositionBool();
		m_UpdateBool = graphics.GetUpdateBool();
		m_MoveBool = graphics.GetMoveBool();
		m_KeyStateBool = graphics.GetKeyStateBool();
		m_HUDBool = graphics.GetHUDBool();
		m_EyeBool = graphics.GetEyeBool();
		m_StickShadowBool = graphics.GetStickShadowBool();
		m_MultipleShadowBool = graphics.GetMultipleShadowBool();
		m_MovingShadowBool = graphics.GetMovingShadowBool();
		m_LightMarkerBool = graphics.GetLightMarkerBool();

		m_TimeElapsed = graphics.GetTimeElapsed();
		m_TimeOffset = graphics.GetTimeOffset();
		m_ObjectState = graphics.GetObjectState();
		m_UpdateCount = graphics.GetUpdateCount();
		m_RenderState = graphics.GetRenderState();
	}

	return *this;
}

Graphics::~Graphics()
{
	try
	{
		delete[] m_Light;

		for (int i = 0; i < m_Path.size(); i++)
		{
			delete m_Path.at(i);
		}

		delete m_Particles;

		delete m_Image;

		delete m_ModelShader;

		delete m_ShadowShader;

		// Release the model object.
		for (int i = 0; i < m_Models.size(); i++)
		{
			delete m_Models.at(i);
		}

		// Release the camera object.
		delete m_View;

		// Release the D3D object.
		delete m_Direct3D;
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

bool Graphics::Update(const int fps, const int cpu, const float dt, const float timeScale)
{
	float calibratedTime = 0.0f;

	if (!m_PauseBool)
	{
		calibratedTime = (dt / 60) * timeScale;
	}

	if (m_ObjectState > 0.0f)
	{
		m_TimeElapsed += calibratedTime;

		if (m_TimeElapsed > 3.0f)
		{
			m_ObjectState = 2.0f;

			if (m_UpdateBool)
			{
				m_ObjectState = 3.0f;

				if (!m_TimeOffsetBool)
				{
					m_TimeOffset = m_TimeElapsed;

					m_TimeOffsetBool = true;
				}

				if (m_TimeElapsed > m_TimeOffset + 3.0f)
				{
					m_ObjectState = 0.0f;

					m_TimeElapsed = 0.0f;
				}
			}
		}
	}
	else
	{
		m_TimeElapsed = 0.0f;
		m_TimeOffset = 0.0f;
		m_UpdateCount = 0;

		m_TimeOffsetBool = false;
		m_UpdateBool = false;
		m_MoveBool = false;

		for (int i = 0; i < m_Models.size(); i++)
		{
			m_Models.at(i)->SetStartPositionBool(false);
			m_Models.at(i)->SetStartRotationBool(false);
		}
	}

	bool updateOver = false;

	if (m_UpdateCount == m_Path.size())
	{
		m_Models.at(0)->Update(m_ObjectState, calibratedTime, m_Models.at(0)->GetStartPosition(), atan2f(m_Models.at(0)->GetPosition().x - m_Models.at(0)->GetStartPosition().x, m_Models.at(0)->GetPosition().z - m_Models.at(0)->GetStartPosition().z) * (180.f / 3.141592653589793238462643383279502884f), m_UpdateBool, m_MoveBool);
		m_Models.at(1)->Update(m_ObjectState, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetInitialPosition(), m_Models.at(0)->GetRotation());
		m_Models.at(2)->Update(m_ObjectState, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetInitialPosition(), m_Models.at(0)->GetRotation());
	}
	else
	{
		if (m_UpdateCount > m_Path.size())
		{
			m_Models.at(0)->Update(m_ObjectState, calibratedTime, m_Models.at(0)->GetStartPosition(), m_Models.at(0)->GetStartRotation().y, m_UpdateBool, m_MoveBool);
			m_Models.at(1)->Update(m_ObjectState, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetInitialPosition(), m_Models.at(0)->GetRotation());
			m_Models.at(2)->Update(m_ObjectState, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetInitialPosition(), m_Models.at(0)->GetRotation());

			updateOver = true;
		}
		else
		{
			m_Models.at(0)->Update(m_ObjectState, calibratedTime, *m_Path[m_UpdateCount], atan2f(m_Models.at(0)->GetPosition().x - m_Path[m_UpdateCount]->x, m_Models.at(0)->GetPosition().z - m_Path[m_UpdateCount]->z) * (180.f / 3.141592653589793238462643383279502884f), m_UpdateBool, m_MoveBool);
			m_Models.at(1)->Update(m_ObjectState, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetInitialPosition(), m_Models.at(0)->GetRotation());
			m_Models.at(2)->Update(m_ObjectState, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetInitialPosition(), m_Models.at(0)->GetRotation());
		}
	}

	if (m_UpdateBool)
	{
		if (!updateOver)
		{
			m_UpdateCount++;

			m_UpdateBool = false;
			m_MoveBool = false;
		}
	}

	m_Image->Update(m_Direct3D->GetDeviceContext(), m_Direct3D->GetScreen(), fps, cpu, timeScale);

	if (m_TrackingViewBool)
	{
		m_View->Update(m_ViewPositionBool, m_ViewEyePositionBool, m_Models.at(0)->GetPosition(), m_Models.at(0)->GetRotation());
	}

	m_Light[2].Update(calibratedTime);

	if (m_ObjectState > 0.0f)
	{
		m_Particles->Update(m_Direct3D->GetDeviceContext(), m_Models.at(0)->GetPosition(), XMFLOAT3(m_View->GetPosition().x, m_View->GetPosition().y, m_View->GetPosition().z), true, calibratedTime);
	}
	else
	{
		m_Particles->Update(m_Direct3D->GetDeviceContext(), m_Models.at(0)->GetPosition(), XMFLOAT3(m_View->GetPosition().x, m_View->GetPosition().y, m_View->GetPosition().z), false, calibratedTime);
	}

	// Render the graphics scene.
	if (!Render())
	{
		return false;
	}

	return true;
}


bool Graphics::Render()
{
	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.1f, 0.6f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_View->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	XMMATRIX worldMatrix = m_Direct3D->GetWorldMatrix();
	XMMATRIX viewMatrix = m_View->GetViewMatrix();
	XMMATRIX projectionMatrix = m_Direct3D->GetProjectionMatrix();

	XMFLOAT4 const shadowPlane = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	array<float, 4> blend =
	{
		0.0f,
		0.0f,
		0.0f,
		0.0f
	};

	if (m_RenderState > 0.0f)
	{
		m_Direct3D->GetDeviceContext()->RSSetState(m_Direct3D->GetSolidRasteriserState());
	}
	else
	{
		m_Direct3D->GetDeviceContext()->RSSetState(m_Direct3D->GetWireframeRasteriserState());
	}

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Models.at(0)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);

	if (m_EyeBool)
	{
		worldMatrix = m_Direct3D->GetWorldMatrix();
		viewMatrix = m_View->GetViewMatrix();
		projectionMatrix = m_Direct3D->GetProjectionMatrix();

		// Model
		m_Models.at(1)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);
	}

	worldMatrix = m_Direct3D->GetWorldMatrix();
	viewMatrix = m_View->GetViewMatrix();
	projectionMatrix = m_Direct3D->GetProjectionMatrix();

	// Model
	m_Models.at(3)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);

	worldMatrix = m_Direct3D->GetWorldMatrix();
	viewMatrix = m_View->GetViewMatrix();
	projectionMatrix = m_Direct3D->GetProjectionMatrix();

	// Model
	m_Models.at(4)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);

	if (m_LightMarkerBool)
	{
		worldMatrix = m_Direct3D->GetWorldMatrix();
		viewMatrix = m_View->GetViewMatrix();
		projectionMatrix = m_Direct3D->GetProjectionMatrix();

		// Model
		for (int i = 0; i < 3; i++)
		{
			m_Models.at(6)->SetPosition(XMFLOAT3(m_Light[i].GetPosition().x, m_Light[i].GetPosition().y, m_Light[i].GetPosition().z));

			m_Models.at(6)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);
		}
	}

	worldMatrix = m_Direct3D->GetWorldMatrix();
	viewMatrix = m_View->GetViewMatrix();
	projectionMatrix = m_Direct3D->GetProjectionMatrix();

	// Model
	m_Models.at(7)->SetPosition(XMFLOAT3(m_View->GetPositionX(), m_View->GetPositionY(), m_View->GetPositionZ()));
	m_Models.at(7)->SetRotation(XMFLOAT3(m_View->GetRotationX(), m_View->GetRotationY(), m_View->GetRotationZ()));

	m_Models.at(7)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);

	worldMatrix = m_Direct3D->GetWorldMatrix();
	viewMatrix = m_View->GetViewMatrix();
	projectionMatrix = m_Direct3D->GetProjectionMatrix();

	// Alpha on
	m_Direct3D->GetDeviceContext()->OMSetBlendState(m_Direct3D->GetEnableAlphaBlendState(), blend.data(), 0xffffffff);

	// Particles
	m_Particles->Render(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_RenderState);

	worldMatrix = m_Direct3D->GetWorldMatrix();
	viewMatrix = m_View->GetViewMatrix();
	projectionMatrix = m_Direct3D->GetProjectionMatrix();

	// Model
	m_Models.at(2)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);

	worldMatrix = m_Direct3D->GetWorldMatrix();
	viewMatrix = m_View->GetViewMatrix();
	projectionMatrix = m_Direct3D->GetProjectionMatrix();

	// Model
	m_Models.at(5)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);

	// Shadows
	m_Models.at(0)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[0].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.005f, 1.25f));

	if (m_MultipleShadowBool)
	{
		m_Models.at(0)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[1].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.01f, -0.75f));

		if (m_MovingShadowBool)
		{
			m_Models.at(0)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[2].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.015f, 0.0f));
		}
	}

	// Shadows
	m_Models.at(2)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[0].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.02f, 1.25f));

	if (m_MultipleShadowBool)
	{
		m_Models.at(2)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[1].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.025f, -0.75f));

		if (m_MovingShadowBool)
		{
			m_Models.at(2)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[2].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.03f, 0.0f));
		}
	}

	// Shadows
	if (m_StickShadowBool)
	{
		m_Models.at(3)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[0].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.04f, 0.0f));

		if (m_MultipleShadowBool)
		{
			m_Models.at(3)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[1].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.045f, 0.0f));

			if (m_MovingShadowBool)
			{
				m_Models.at(3)->Render(m_Direct3D->GetDeviceContext(), m_ShadowShader, worldMatrix, viewMatrix, projectionMatrix, XMMatrixShadow(XMLoadFloat4(&shadowPlane), XMLoadFloat4(&m_Light[2].GetPosition())), m_Light, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset, XMFLOAT3(0.0f, 1.05f, 0.0f));
			}
		}
	}

	for (int i = 8; i < m_Models.size(); i++)
	{
		// Models
		m_Models.at(i)->Render(m_Direct3D->GetDeviceContext(), m_ModelShader, worldMatrix, viewMatrix, projectionMatrix, m_Light, m_View, m_ObjectState, m_RenderState, m_TimeElapsed, m_TimeOffset);
	}

	// Alpha off
	m_Direct3D->GetDeviceContext()->OMSetBlendState(m_Direct3D->GetDisableAlphaBlendState(), blend.data(), 0xffffffff);

	// Images
	if (m_HUDBool)
	{
		worldMatrix = m_Direct3D->GetWorldMatrix();
		viewMatrix = m_View->GetViewMatrix();
		projectionMatrix = m_Direct3D->GetProjectionMatrix();
		XMMATRIX orthographicMatrix = m_Direct3D->GetOrthographicMatrix();

		m_Direct3D->GetDeviceContext()->RSSetState(m_Direct3D->GetSolidRasteriserState());
		m_Direct3D->GetDeviceContext()->OMSetDepthStencilState(m_Direct3D->GetDisabledDepthStencilState(), 1);
		m_Direct3D->GetDeviceContext()->OMSetBlendState(m_Direct3D->GetEnableAlphaBlendState(), blend.data(), 0xffffffff);

		m_Image->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthographicMatrix);

		m_Direct3D->GetDeviceContext()->OMSetBlendState(m_Direct3D->GetDisableAlphaBlendState(), blend.data(), 0xffffffff);
		m_Direct3D->GetDeviceContext()->OMSetDepthStencilState(m_Direct3D->GetDepthStencilState(), 1);
	}

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}