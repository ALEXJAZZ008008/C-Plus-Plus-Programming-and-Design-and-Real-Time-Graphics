#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <array>
#include "modelVertex.h"
#include "face.h"

using namespace std;
using namespace DirectX;

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	void LoadModel(ModelVertex *&, long *&, int &) const;
	void LoadModel(const char * const, const char * const, ModelVertex *&, long *&, int &, const XMFLOAT3 &) const;
	void ReadFile(const char * const, int &, int &, int &, int &) const;
	void WriteDataStructure(const char * const, const char * const, const int, const int, const int, const int) const;
	const float VertexMagnitude(const XMFLOAT3 &) const;
	void NormaliseModel(ModelVertex * const &, const int, const XMFLOAT3 &) const;
	void CalculateLightingVertices(ModelVertex * const &, const int) const;
	void CalculateTangentBinormal(const ModelVertex * const, XMFLOAT3 * const) const;
};