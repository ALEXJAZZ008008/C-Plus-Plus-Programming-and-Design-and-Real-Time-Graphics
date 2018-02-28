#pragma once

#include <directxmath.h>
#include <array>
#include <vector>
#include "view.h"
#include "model.h"
#include "light.h"

using namespace std;
using namespace DirectX;

class GraphicsLoader
{
public:
	GraphicsLoader();
	explicit GraphicsLoader(const char *);
	GraphicsLoader(const GraphicsLoader &);
	GraphicsLoader & operator = (const GraphicsLoader &);
	GraphicsLoader(const GraphicsLoader &&);
	GraphicsLoader & operator = (const GraphicsLoader &&);
	~GraphicsLoader();

	const View * GetView() const
	{
		return m_View;
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

	void SetView(View * const view)
	{
		m_View = view;
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

	void LoadGraphics(const char *);

private:
	View *m_View;
	vector<Model *> m_Models;
	Light *m_Light;
	vector<XMFLOAT3 *> m_Path;
};