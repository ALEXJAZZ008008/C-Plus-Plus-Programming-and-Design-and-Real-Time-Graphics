#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <iostream>
#include <array>
#include "modelVertex.h"
#include "modelLoader.h"
#include "modelShader.h"
#include "shadowShader.h"
#include "textureArray.h"
#include "light.h"
#include "view.h"

using namespace std;
using namespace DirectX;

class Model
{
public:
	Model();
	Model(ID3D11Device *, ID3D11DeviceContext *, const ModelLoader * const);
	Model(ID3D11Device *, ID3D11DeviceContext * const, const ModelLoader * const, const char *, const char *, const char *, const char *, const XMFLOAT4 &, const XMFLOAT3 &, const XMFLOAT3 &, const XMFLOAT3 &, const float, const float, const float);
	Model(const char *, const char *, const char *, const char *, const XMFLOAT4 &, const XMFLOAT3 &, const XMFLOAT3 &, const XMFLOAT3 &, const float, const float, const float);
	Model(const Model &);
	Model & operator = (const Model &);
	Model(const Model &&);
	Model & operator = (const Model &&);
	~Model();

	const TextureArray * GetTextureArray() const
	{
		return m_TextureArray;
	}

	ID3D11Buffer * GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}

	ID3D11Buffer * GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	const char * GetModelFilename() const
	{
		return m_ModelFilename;
	}

	const char * GetTextureFilename() const
	{
		return m_TextureFilename;
	}

	const char * GetBumpMapFilename() const
	{
		return m_BumpMapFilename;
	}

	const char * GetSpecularMapFilename() const
	{
		return m_SpecularMapFilename;
	}

	const XMFLOAT4 & GetColour() const
	{
		return m_Colour;
	}

	const XMFLOAT3 & GetInitialPosition() const
	{
		return m_InitialPosition;
	}

	const XMFLOAT3 & GetStartPosition() const
	{
		return m_StartPosition;
	}

	const XMFLOAT3 & GetPosition() const
	{
		return m_Position;
	}

	const XMFLOAT3 & GetInitialRotation() const
	{
		return m_InitialRotation;
	}

	const XMFLOAT3 & GetStartRotation() const
	{
		return m_StartRotation;
	}

	const XMFLOAT3 & GetRotation() const
	{
		return m_Rotation;
	}

	const XMFLOAT3 & GetSize() const
	{
		return m_Size;
	}

	const bool GetStartPositionBool() const
	{
		return m_StartPositionBool;
	}

	const bool GetStartRotationBool() const
	{
		return m_StartRotationBool;
	}

	const int GetCount() const
	{
		return m_Count;
	}

	const float GetObjectType() const
	{
		return m_ObjectType;
	}

	const float GetVelocity() const
	{
		return m_Velocity;
	}

	const float GetReflectivity() const
	{
		return m_Reflectivity;
	}

	const float GetBlendAmount() const
	{
		return m_BlendAmount;
	}

	void SetTextureArray(TextureArray * const textureArray)
	{
		m_TextureArray = textureArray;
	}

	void SetVertexBuffer(ID3D11Buffer * const vertexBuffer)
	{
		m_VertexBuffer = vertexBuffer;
	}

	void SetIndexBuffer(ID3D11Buffer * const indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}

	void SetModelFilename(char * const modelFilename)
	{
		m_ModelFilename = modelFilename;
	}

	void SetTextureFilename(char * const textureFilename)
	{
		m_TextureFilename = textureFilename;
	}

	void SetBumpMapFilename(char * const bumpMapFilename)
	{
		m_BumpMapFilename = bumpMapFilename;
	}

	void SetSpecularMapFilename(char * const specularMapFilename)
	{
		m_SpecularMapFilename = specularMapFilename;
	}

	void SetColour(const XMFLOAT4 &colour)
	{
		m_Colour = colour;
	}

	void SetInitialPosition(const XMFLOAT3 &initialPosition)
	{
		m_InitialPosition = initialPosition;
	}

	void SetStartPosition(const XMFLOAT3 &startPosition)
	{
		m_StartPosition = startPosition;
	}

	void SetPosition(const XMFLOAT3 &position)
	{
		m_Position = position;
	}

	void SetInitialRotation(const XMFLOAT3 &initialRotation)
	{
		m_InitialRotation = initialRotation;
	}

	void SetStartRotation(const XMFLOAT3 &startRotation)
	{
		m_StartRotation = startRotation;
	}

	void SetRotation(const XMFLOAT3 &rotation)
	{
		m_Rotation = rotation;
	}

	void SetSize(const XMFLOAT3 &size)
	{
		m_Size = size;
	}

	void SetStartPositionBool(const bool startPositionBool)
	{
		m_StartPositionBool = startPositionBool;
	}

	void SetStartRotationBool(const bool startRotationBool)
	{
		m_StartRotationBool = startRotationBool;
	}

	void SetCount(const int count)
	{
		m_Count = count;
	}

	void SetObjectType(const float objectType)
	{
		m_ObjectType = objectType;
	}

	void SetVelocity(const float velocity)
	{
		m_Velocity = velocity;
	}

	void SetReflectivity(const float reflectivity)
	{
		m_Reflectivity = reflectivity;
	}

	void SetBlendAmount(const float blendAmount)
	{
		m_BlendAmount = blendAmount;
	}

	void Update(const float, const XMFLOAT3 &, const XMFLOAT3 &, const XMFLOAT3 &);
	void Update(const float, const float, const XMFLOAT3 &, const float, bool &, bool &);
	void Render(ID3D11DeviceContext * const, const ShadowShader * const, const XMMATRIX &, const XMMATRIX &, const XMMATRIX &, const XMMATRIX &, const Light * const, const float, const float, const float, const float, const XMFLOAT3 &) const;
	void Render(ID3D11DeviceContext * const, const ModelShader * const, const XMMATRIX &, const XMMATRIX &, const XMMATRIX &, const Light * const, const View *, const float, const float, const float, const float) const;

private:
	TextureArray *m_TextureArray;
	ID3D11Buffer *m_VertexBuffer;
	ID3D11Buffer *m_IndexBuffer;
	char *m_ModelFilename;
	char *m_TextureFilename;
	char *m_BumpMapFilename;
	char *m_SpecularMapFilename;
	XMFLOAT4 m_Colour;
	XMFLOAT3 m_InitialPosition, m_StartPosition, m_Position, m_InitialRotation, m_StartRotation, m_Rotation, m_Size;
	bool m_StartPositionBool, m_StartRotationBool;
	int m_Count;
	float m_ObjectType, m_Velocity, m_Reflectivity, m_BlendAmount;
};