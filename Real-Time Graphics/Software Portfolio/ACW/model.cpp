#include "model.h"

Model::Model() : m_TextureArray(nullptr), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_ModelFilename(nullptr), m_TextureFilename(nullptr), m_BumpMapFilename(nullptr), m_SpecularMapFilename(nullptr), m_Colour(), m_InitialPosition(), m_StartPosition(), m_Position(), m_InitialRotation(), m_StartRotation(), m_Rotation(), m_Size(), m_StartPositionBool(false), m_StartRotationBool(false), m_Count(0), m_ObjectType(0.0f), m_Velocity(0.0f), m_Reflectivity(0.0f), m_BlendAmount(0.0f)
{
	
}

Model::Model(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, const ModelLoader * const modelLoader) : m_TextureArray(new TextureArray(device, deviceContext, "../ACW/models/cube/cubeTexture.tga", "../ACW/models/cube/cubeBumpMap.tga", "../ACW/models/cube/cubeSpecularMap.tga")), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_ModelFilename(nullptr), m_TextureFilename(nullptr), m_BumpMapFilename(nullptr), m_SpecularMapFilename(nullptr), m_Colour(), m_InitialPosition(), m_StartPosition(), m_Position(), m_InitialRotation(), m_StartRotation(), m_Rotation(), m_Size(), m_StartPositionBool(false), m_StartRotationBool(false), m_Count(0), m_ObjectType(0.0f), m_Velocity(0.0f), m_Reflectivity(64.0f), m_BlendAmount(1.0f)
{
	// Initialize the vertex and index buffers.
	// Create the vertex array.
	ModelVertex *vertices = nullptr;

	// Create the index array.
	long *indices = nullptr;

	modelLoader->LoadModel(vertices, indices, m_Count);

	D3D11_BUFFER_DESC vertexBufferDesc =
	{
		sizeof(vertexBufferDesc)
	};

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ModelVertex) * m_Count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData =
	{

	};

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc =
	{
		sizeof(indexBufferDesc)
	};

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(long) * m_Count;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData =
	{

	};

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;

	delete[] indices;
}

Model::Model(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, const ModelLoader * const modelLoader, const char * const modelFilename, const char * const textureFilename, const char * const bumpMapFilename, const char * const specularMapFilename, const XMFLOAT4 &colour, const XMFLOAT3 &size, const XMFLOAT3 &initialPosition, const XMFLOAT3 &initialRotation, const float objectType, const float reflectivity, const float blendAmount) : m_TextureArray(new TextureArray(device, deviceContext, textureFilename, bumpMapFilename, specularMapFilename)), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_ModelFilename(nullptr), m_TextureFilename(nullptr), m_BumpMapFilename(nullptr), m_SpecularMapFilename(nullptr), m_Colour(colour), m_InitialPosition(initialPosition), m_StartPosition(), m_Position(), m_InitialRotation(initialRotation), m_StartRotation(), m_Rotation(), m_Size(size), m_StartPositionBool(false), m_StartRotationBool(false), m_Count(0), m_ObjectType(objectType), m_Velocity(0.5f), m_Reflectivity(reflectivity), m_BlendAmount(blendAmount)
{
	size_t stringLength = strlen(modelFilename) + 1;
	m_ModelFilename = new char[stringLength];
	strcpy_s(m_ModelFilename, stringLength, const_cast<char *>(modelFilename));

	stringLength = strlen(textureFilename) + 1;
	m_TextureFilename = new char[stringLength];
	strcpy_s(m_TextureFilename, stringLength, const_cast<char *>(textureFilename));

	stringLength = strlen(bumpMapFilename) + 1;
	m_BumpMapFilename = new char[stringLength];
	strcpy_s(m_BumpMapFilename, stringLength, const_cast<char *>(bumpMapFilename));

	stringLength = strlen(specularMapFilename) + 1;
	m_SpecularMapFilename = new char[stringLength];
	strcpy_s(m_SpecularMapFilename, stringLength, const_cast<char *>(specularMapFilename));

	m_Position = m_InitialPosition;

	m_Rotation = m_InitialRotation;

	array<char, 64> modelSize =
	{

	};

	array<char, 64> temporaryModelSize =
	{

	};

	array<char, 64> outputModelSize =
	{

	};

	char *token = nullptr;

	sprintf_s(temporaryModelSize.data(), temporaryModelSize.size(), "%f", size.x);

	strcpy_s(modelSize.data(), modelSize.size(), temporaryModelSize.data());
	strcat_s(modelSize.data(), modelSize.size(), ",");

	sprintf_s(temporaryModelSize.data(), temporaryModelSize.size(), "%f", size.y);

	strcat_s(modelSize.data(), modelSize.size(), temporaryModelSize.data());
	strcat_s(modelSize.data(), modelSize.size(), ",");

	sprintf_s(temporaryModelSize.data(), temporaryModelSize.size(), "%f", size.z);

	strcat_s(modelSize.data(), modelSize.size(), temporaryModelSize.data());

	strcpy_s(temporaryModelSize.data(), temporaryModelSize.size(), strtok_s(modelSize.data(), ".", &token));
	strcat_s(outputModelSize.data(), outputModelSize.size(), temporaryModelSize.data());

	strcpy_s(temporaryModelSize.data(), temporaryModelSize.size(), strtok_s(nullptr, ".", &token));
	strcat_s(outputModelSize.data(), outputModelSize.size(), temporaryModelSize.data());

	strcpy_s(temporaryModelSize.data(), temporaryModelSize.size(), strtok_s(nullptr, ".", &token));
	strcat_s(outputModelSize.data(), outputModelSize.size(), temporaryModelSize.data());

	strcpy_s(temporaryModelSize.data(), temporaryModelSize.size(), strtok_s(nullptr, ".", &token));
	strcat_s(outputModelSize.data(), outputModelSize.size(), temporaryModelSize.data());

	array<char, 128> temporaryModelFilename =
	{

	};

	strcpy_s(temporaryModelFilename.data(), temporaryModelFilename.size(), modelFilename);

	int temporaryModelFilenameEnd = 0;

	for (int i = 0; i < temporaryModelFilename.size(); i++)
	{
		if (temporaryModelFilename.at(i) == '\0')
		{
			temporaryModelFilenameEnd = i;

			break;
		}
	}

	temporaryModelFilename.at(temporaryModelFilenameEnd - 4) = '\0';

	strcat_s(temporaryModelFilename.data(), temporaryModelFilename.size(), outputModelSize.data());
	strcat_s(temporaryModelFilename.data(), temporaryModelFilename.size(), ".xyz");

	// Initialize the vertex and index buffers.
	// Create the vertex array.
	ModelVertex *vertices = nullptr;

	// Create the index array.
	long *indices = nullptr;

	modelLoader->LoadModel(modelFilename, temporaryModelFilename.data(), vertices, indices, m_Count, size);

	D3D11_BUFFER_DESC vertexBufferDesc =
	{
		sizeof(vertexBufferDesc)
	};

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ModelVertex) * m_Count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData =
	{

	};

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc =
	{
		sizeof(indexBufferDesc)
	};

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(long) * m_Count;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData =
	{

	};

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;

	delete[] indices;
}

Model::Model(const char * const modelFilename, const char * const textureFilename, const char * const bumpMapFilename, const char * const specularMapFilename, const XMFLOAT4 &colour, const XMFLOAT3 &size, const XMFLOAT3 &initialPosition, const XMFLOAT3 &initialRotation, const float objectType, const float reflectivity, const float blendAmount) : m_TextureArray(nullptr), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_ModelFilename(nullptr), m_TextureFilename(nullptr), m_BumpMapFilename(nullptr), m_SpecularMapFilename(nullptr), m_Colour(colour), m_InitialPosition(initialPosition), m_StartPosition(), m_Position(), m_InitialRotation(initialRotation), m_StartRotation(), m_Rotation(), m_Size(size), m_StartPositionBool(false), m_StartRotationBool(false), m_Count(0), m_ObjectType(objectType), m_Velocity(0.5f), m_Reflectivity(reflectivity), m_BlendAmount(blendAmount)
{
	size_t stringLength = strlen(modelFilename) + 1;
	m_ModelFilename = new char[stringLength];
	strcpy_s(m_ModelFilename, stringLength, const_cast<char *>(modelFilename));

	stringLength = strlen(textureFilename) + 1;
	m_TextureFilename = new char[stringLength];
	strcpy_s(m_TextureFilename, stringLength, const_cast<char *>(textureFilename));

	stringLength = strlen(bumpMapFilename) + 1;
	m_BumpMapFilename = new char[stringLength];
	strcpy_s(m_BumpMapFilename, stringLength, const_cast<char *>(bumpMapFilename));

	stringLength = strlen(specularMapFilename) + 1;
	m_SpecularMapFilename = new char[stringLength];
	strcpy_s(m_SpecularMapFilename, stringLength, const_cast<char *>(specularMapFilename));

	m_Position = m_InitialPosition;

	m_Rotation = m_InitialRotation;
}

Model::Model(const Model &model) : m_TextureArray(const_cast<TextureArray *>(model.GetTextureArray())), m_VertexBuffer(model.GetVertexBuffer()), m_IndexBuffer(model.GetIndexBuffer()), m_ModelFilename(const_cast<char *>(model.GetModelFilename())), m_TextureFilename(const_cast<char *>(model.GetTextureFilename())), m_BumpMapFilename(const_cast<char *>(model.GetBumpMapFilename())), m_SpecularMapFilename(const_cast<char *>(model.GetSpecularMapFilename())), m_Colour(model.GetColour()), m_InitialPosition(model.GetInitialPosition()), m_StartPosition(model.GetStartPosition()), m_Position(model.GetPosition()), m_InitialRotation(model.GetInitialRotation()), m_StartRotation(model.GetStartRotation()), m_Rotation(model.GetRotation()), m_Size(model.GetSize()), m_StartPositionBool(model.GetStartPositionBool()), m_StartRotationBool(model.GetStartRotationBool()), m_Count(model.GetCount()), m_ObjectType(model.GetObjectType()), m_Velocity(model.GetVelocity()), m_Reflectivity(model.GetReflectivity()), m_BlendAmount(model.GetBlendAmount())
{

}

Model & Model::operator = (const Model &model)
{
	if (this != &model)
	{
		m_TextureArray = const_cast<TextureArray *>(model.GetTextureArray());
		m_VertexBuffer = model.GetVertexBuffer();
		m_IndexBuffer = model.GetIndexBuffer();
		m_ModelFilename = const_cast<char *>(model.GetModelFilename());
		m_TextureFilename = const_cast<char *>(model.GetTextureFilename());
		m_BumpMapFilename = const_cast<char *>(model.GetBumpMapFilename());
		m_SpecularMapFilename = const_cast<char *>(model.GetSpecularMapFilename());

		m_Colour = model.GetColour();
		m_InitialPosition = model.GetInitialPosition();
		m_StartPosition = model.GetStartPosition();
		m_Position = model.GetPosition();
		m_InitialRotation = model.GetInitialRotation();
		m_StartRotation = model.GetStartRotation();
		m_Rotation = model.GetRotation();
		m_Size = model.GetSize();

		m_StartPositionBool = model.GetStartPositionBool();
		m_StartRotationBool = model.GetStartRotationBool();

		m_Count = model.GetCount();
		m_ObjectType = model.GetObjectType();
		m_Velocity = model.GetVelocity();
		m_Reflectivity = model.GetReflectivity();
		m_BlendAmount = model.GetBlendAmount();
	}

	return *this;
}

Model::Model(const Model &&model) : m_TextureArray(const_cast<TextureArray *>(model.GetTextureArray())), m_VertexBuffer(model.GetVertexBuffer()), m_IndexBuffer(model.GetIndexBuffer()), m_ModelFilename(const_cast<char *>(model.GetModelFilename())), m_TextureFilename(const_cast<char *>(model.GetTextureFilename())), m_BumpMapFilename(const_cast<char *>(model.GetBumpMapFilename())), m_SpecularMapFilename(const_cast<char *>(model.GetSpecularMapFilename())), m_Colour(model.GetColour()), m_InitialPosition(model.GetInitialPosition()), m_StartPosition(model.GetStartPosition()), m_Position(model.GetPosition()), m_InitialRotation(model.GetInitialRotation()), m_StartRotation(model.GetStartRotation()), m_Rotation(model.GetRotation()), m_Size(model.GetSize()), m_StartPositionBool(model.GetStartPositionBool()), m_StartRotationBool(model.GetStartRotationBool()), m_Count(model.GetCount()), m_ObjectType(model.GetObjectType()), m_Velocity(model.GetVelocity()), m_Reflectivity(model.GetReflectivity()), m_BlendAmount(model.GetBlendAmount())
{

}

Model & Model::operator = (const Model &&model)
{
	if (this != &model)
	{
		m_TextureArray = const_cast<TextureArray *>(model.GetTextureArray());
		m_VertexBuffer = model.GetVertexBuffer();
		m_IndexBuffer = model.GetIndexBuffer();
		m_ModelFilename = const_cast<char *>(model.GetModelFilename());
		m_TextureFilename = const_cast<char *>(model.GetTextureFilename());
		m_BumpMapFilename = const_cast<char *>(model.GetBumpMapFilename());
		m_SpecularMapFilename = const_cast<char *>(model.GetSpecularMapFilename());

		m_Colour = model.GetColour();
		m_InitialPosition = model.GetInitialPosition();
		m_StartPosition = model.GetStartPosition();
		m_Position = model.GetPosition();
		m_InitialRotation = model.GetInitialRotation();
		m_StartRotation = model.GetStartRotation();
		m_Rotation = model.GetRotation();
		m_Size = model.GetSize();

		m_StartPositionBool = model.GetStartPositionBool();
		m_StartRotationBool = model.GetStartRotationBool();

		m_Count = model.GetCount();
		m_ObjectType = model.GetObjectType();
		m_Velocity = model.GetVelocity();
		m_Reflectivity = model.GetReflectivity();
		m_BlendAmount = model.GetBlendAmount();
	}

	return *this;
}

Model::~Model()
{
	try
	{
		// Release the model texture.
		// Release the texture object.
		delete m_TextureArray;

		if (m_IndexBuffer != nullptr)
		{
			// Shutdown the vertex and index buffers.
			// Release the index buffer.
			m_IndexBuffer->Release();
		}

		delete[] m_ModelFilename;
		delete[] m_TextureFilename;
		delete[] m_BumpMapFilename;
		delete[] m_SpecularMapFilename;

		if (m_VertexBuffer != nullptr)
		{
			// Release the vertex buffer.
			m_VertexBuffer->Release();
		}
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void Model::Update(const float objectState, const XMFLOAT3 &position, const XMFLOAT3 &initialPosition, const XMFLOAT3 &rotation)
{
	if (objectState < 1.0f)
	{
		m_StartPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_StartRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		if (objectState > 0.0f && objectState < 2.0f)
		{
			m_Position.y = (position.y + (m_InitialPosition.y - initialPosition.y));
		}
		else
		{
			if (objectState > 1.0f && objectState < 3.0f)
			{
				if (!m_StartPositionBool)
				{
					m_StartPosition = m_Position;

					m_StartPositionBool = true;
				}

				if (!m_StartRotationBool)
				{
					m_StartRotation = m_Rotation;

					m_StartRotationBool = true;
				}

				m_Position = XMFLOAT3(position.x + (m_InitialPosition.x - initialPosition.x), position.y + (m_InitialPosition.y - initialPosition.y), position.z + (m_InitialPosition.z - initialPosition.z));
				m_Rotation = rotation;
			}
			else
			{
				if (objectState > 2.0f)
				{
					m_Position.y = (position.y + (m_InitialPosition.y - initialPosition.y));
				}
			}
		}
	}
}

void Model::Update(const float objectState, const float dt, const XMFLOAT3 &position, const float rotation, bool &updateBool, bool &moveBool)
{
	if (objectState < 1.0f)
	{
		m_StartPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_StartRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		if (objectState > 0.0f && objectState < 2.0f)
		{
			m_Position.y = (m_Position.y + (m_Velocity * dt));
		}
		else
		{
			if (objectState > 1.0f && objectState < 3.0f)
			{
				if (!m_StartPositionBool)
				{
					m_StartPosition = m_Position;

					m_StartPositionBool = true;
				}

				if (!m_StartRotationBool)
				{
					m_StartRotation = m_Rotation;

					m_StartRotationBool = true;
				}

				float finalRotation = rotation;

				if (finalRotation > 360.0f)
				{
					finalRotation = 0.0f + (finalRotation - 360.0f);
				}
				else
				{
					if (finalRotation < 0.0f)
					{
						finalRotation = 360.0f + finalRotation;
					}
				}

				if (fabs(m_Rotation.y - finalRotation) > 1.0f && !moveBool)
				{
					if (m_Rotation.y < finalRotation)
					{
						m_Rotation.y = (m_Rotation.y + ((m_Velocity * 40) * dt));
					}
					else
					{
						m_Rotation.y = (m_Rotation.y - ((m_Velocity * 40) * dt));
					}

					if (m_Rotation.y > 360.0f)
					{
						m_Rotation.y = (0.0f + (m_Rotation.y - 360.0f));
					}
					else
					{
						if (m_Rotation.y < 0.0f)
						{
							m_Rotation.y = (360.0f + m_Rotation.y);
						}
					}

					updateBool = false;
				}
				else
				{
					XMFLOAT3 finalPosition = position;

					if (finalPosition.y < 0.5f)
					{
						finalPosition.y = (0.5f);
					}

					const XMFLOAT3 midpoint = XMFLOAT3(finalPosition.x / 2.0f, finalPosition.y / 2.0f, finalPosition.z / 2.0f);

					while (true)
					{
						if (sqrt(pow(finalPosition.x, 2) + pow(finalPosition.y, 2) + pow(finalPosition.z, 2)) > 4.0f)
						{
							finalPosition.x = (finalPosition.x - (midpoint.x * 0.01f));
							finalPosition.y = (finalPosition.y - (midpoint.y * 0.01f));
							finalPosition.z = (finalPosition.z - (midpoint.z * 0.01f));
						}
						else
						{
							break;
						}
					}

					while (true)
					{
						if (sqrt(pow(finalPosition.x, 2) + pow(finalPosition.y, 2) + pow(finalPosition.z, 2)) < 2.0f)
						{
							finalPosition.x = (finalPosition.x + (midpoint.x * 0.01f));
							finalPosition.y = (finalPosition.y + (midpoint.y * 0.01f));
							finalPosition.z = (finalPosition.z + (midpoint.z * 0.01f));
						}
						else
						{
							break;
						}
					}

					for (int i = 0; i < 100; i++)
					{
						const XMFLOAT3 testVector = XMFLOAT3(m_Position.x + ((finalPosition.x / 100) * i), m_Position.y + ((finalPosition.y / 100) * i), m_Position.z + ((finalPosition.z / 100) * i));

						if (sqrt(pow(testVector.x, 2) + pow(testVector.y, 2) + pow(testVector.z, 2)) < 2.0f)
						{
							finalPosition = XMFLOAT3((finalPosition.x + m_Position.x) / 2, (finalPosition.y + (m_Position.y + 1.0f)) / 2, (finalPosition.z + m_Position.z) / 2);

							i = 0;
						}
					}

					if (sqrt(pow(m_Position.x - finalPosition.x, 2) + pow(m_Position.y - finalPosition.y, 2) + pow(m_Position.z - finalPosition.z, 2)) > 0.005)
					{
						XMFLOAT3 movementDirection = XMFLOAT3(finalPosition.x - m_Position.x, finalPosition.y - m_Position.y, finalPosition.z - m_Position.z);

						const float magnitude = sqrt(pow(movementDirection.x, 2) + pow(movementDirection.y, 2) + pow(movementDirection.z, 2));
						movementDirection = XMFLOAT3(movementDirection.x / magnitude, movementDirection.y / magnitude, movementDirection.z / magnitude);

						const XMFLOAT3 velocity = XMFLOAT3(movementDirection.x * m_Velocity, movementDirection.y * m_Velocity, movementDirection.z * m_Velocity);

						m_Position = XMFLOAT3(m_Position.x + (velocity.x * dt), m_Position.y + (velocity.y * dt), m_Position.z + (velocity.z * dt));

						updateBool = false;
					}
					else
					{
						updateBool = true;
					}

					moveBool = true;
				}
			}
			else
			{
				if (objectState > 2.0f)
				{
					m_Position.y = (m_Position.y - (m_Velocity * dt));
				}
			}
		}
	}
}

void Model::Render(ID3D11DeviceContext * const deviceContext, const ShadowShader * const shadowShader, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, const XMMATRIX &shadowMatrix, const Light * const light, const float objectState, const float renderState, const float timeElapsed, const float timeOffset, const XMFLOAT3 &m_ShadowPosition) const
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// Set vertex buffer stride and offset.
	unsigned int const stride = sizeof(ModelVertex);
	unsigned int const offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	const XMMATRIX temporaryWorldMatrix = ((worldMatrix * shadowMatrix) * XMMatrixRotationRollPitchYaw(0.0f, m_Rotation.y * (3.141592653589793238462643383279502884f / 180.0f), m_Rotation.z * (3.141592653589793238462643383279502884f / 180.0f))) * XMMatrixTranslation(m_Position.x + m_ShadowPosition.x, m_ShadowPosition.y, m_Position.z + m_ShadowPosition.z);

	shadowShader->Render(deviceContext, m_Count, temporaryWorldMatrix, viewMatrix, projectionMatrix, light, m_ObjectType, objectState, renderState, timeElapsed, timeOffset, m_BlendAmount - 0.20f);
}

void Model::Render(ID3D11DeviceContext * const deviceContext, const ModelShader * const modelShader, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, const Light * const light, const View * const view, const float objectState, const float renderState, const float timeElapsed, const float timeOffset) const
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// Set vertex buffer stride and offset.
	unsigned int const stride = sizeof(ModelVertex);
	unsigned int const offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	const XMMATRIX temporaryWorldMatrix = (worldMatrix * XMMatrixRotationRollPitchYaw(m_Rotation.x * (3.141592653589793238462643383279502884f / 180.0f), m_Rotation.y * (3.141592653589793238462643383279502884f / 180.0f), m_Rotation.z * (3.141592653589793238462643383279502884f / 180.0f))) * XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	modelShader->Render(deviceContext, m_Count, temporaryWorldMatrix, viewMatrix, projectionMatrix, m_TextureArray->GetTextureViews().data(), light, view->GetPosition(), m_Colour, m_Reflectivity, m_ObjectType, objectState, renderState, timeElapsed, timeOffset, m_BlendAmount);
}