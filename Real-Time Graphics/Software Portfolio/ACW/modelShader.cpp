#include "modelShader.h"

ModelShader::ModelShader() : m_VertexShader(nullptr), m_PixelShader(nullptr), m_Layout(nullptr), m_MatrixBuffer(nullptr), m_ObjectBuffer(nullptr), m_LightBuffer(nullptr), m_BlendBuffer(nullptr), m_SampleState(nullptr)
{

}

ModelShader::ModelShader(ID3D11Device * const device) : m_VertexShader(nullptr), m_PixelShader(nullptr), m_Layout(nullptr), m_MatrixBuffer(nullptr), m_ObjectBuffer(nullptr), m_LightBuffer(nullptr), m_BlendBuffer(nullptr), m_SampleState(nullptr)
{
	long shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	shaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	// Initialize the vertex shader.
	// Initialize the pointers this function will use to null.
	ID3D10Blob *vertexShaderBuffer = nullptr;

	// Compile the vertex shader code.
	D3DCompileFromFile(L"../ACW/modelVertexShader.hlsl", nullptr, nullptr, "ModelVertexShader", "vs_5_0", shaderFlags, 0, &vertexShaderBuffer, nullptr);

	// Create the vertex shader from the buffer.
	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_VertexShader);

	// Initialize the pixel shader.
	ID3D10Blob *pixelShaderBuffer = nullptr;

	// Compile the pixel shader code.
	D3DCompileFromFile(L"../ACW/modelPixelShader.hlsl", nullptr, nullptr, "ModelPixelShader", "ps_5_0", shaderFlags, 0, &pixelShaderBuffer, nullptr);

	// Create the pixel shader from the buffer.
	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_PixelShader);

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the Model and in the shader.
	array<D3D11_INPUT_ELEMENT_DESC, 5> layout =
	{
		
	};

	layout.at(0).SemanticName = "POSITION";
	layout.at(0).SemanticIndex = 0;
	layout.at(0).Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layout.at(0).InputSlot = 0;
	layout.at(0).AlignedByteOffset = 0;
	layout.at(0).InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layout.at(0).InstanceDataStepRate = 0;

	layout.at(1).SemanticName = "TEXCOORD";
	layout.at(1).SemanticIndex = 0;
	layout.at(1).Format = DXGI_FORMAT_R32G32_FLOAT;
	layout.at(1).InputSlot = 0;
	layout.at(1).AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layout.at(1).InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layout.at(1).InstanceDataStepRate = 0;

	layout.at(2).SemanticName = "NORMAL";
	layout.at(2).SemanticIndex = 0;
	layout.at(2).Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layout.at(2).InputSlot = 0;
	layout.at(2).AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layout.at(2).InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layout.at(2).InstanceDataStepRate = 0;

	layout.at(3).SemanticName = "TANGENT";
	layout.at(3).SemanticIndex = 0;
	layout.at(3).Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layout.at(3).InputSlot = 0;
	layout.at(3).AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layout.at(3).InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layout.at(3).InstanceDataStepRate = 0;

	layout.at(4).SemanticName = "BINORMAL";
	layout.at(4).SemanticIndex = 0;
	layout.at(4).Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layout.at(4).InputSlot = 0;
	layout.at(4).AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layout.at(4).InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layout.at(4).InstanceDataStepRate = 0;

	// Create the vertex input layout.
	device->CreateInputLayout(layout.data(), static_cast<unsigned int>(layout.size()), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_Layout);

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();

	pixelShaderBuffer->Release();

	D3D11_BUFFER_DESC matrixBufferDesc =
	{
		sizeof(matrixBufferDesc)
	};

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	device->CreateBuffer(&matrixBufferDesc, nullptr, &m_MatrixBuffer);

	D3D11_BUFFER_DESC viewBufferDesc =
	{
		sizeof(viewBufferDesc)
	};

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	viewBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	viewBufferDesc.ByteWidth = sizeof(ObjectBuffer);
	viewBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	viewBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	viewBufferDesc.MiscFlags = 0;
	viewBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	device->CreateBuffer(&viewBufferDesc, nullptr, &m_ObjectBuffer);

	D3D11_SAMPLER_DESC samplerDesc =
	{

	};

	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	device->CreateSamplerState(&samplerDesc, &m_SampleState);

	D3D11_BUFFER_DESC lightBufferDesc =
	{
		sizeof(lightBufferDesc)
	};

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	device->CreateBuffer(&lightBufferDesc, nullptr, &m_LightBuffer);

	D3D11_BUFFER_DESC blendBufferDesc =
	{
		sizeof(blendBufferDesc)
	};

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	blendBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	blendBufferDesc.ByteWidth = sizeof(BlendBuffer);
	blendBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	blendBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	blendBufferDesc.MiscFlags = 0;
	blendBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	device->CreateBuffer(&blendBufferDesc, nullptr, &m_BlendBuffer);
}

ModelShader::ModelShader(const ModelShader &modelShader) : m_VertexShader(modelShader.GetVertexShader()), m_PixelShader(modelShader.GetPixelShader()), m_Layout(modelShader.GetLayout()), m_MatrixBuffer(modelShader.GetMatrixBuffer()), m_ObjectBuffer(modelShader.GetObjectBuffer()), m_LightBuffer(modelShader.GetLightBuffer()), m_BlendBuffer(modelShader.GetBlendBuffer()), m_SampleState(modelShader.GetSampleState())
{

}

ModelShader & ModelShader::operator = (const ModelShader &modelShader)
{
	if (this != &modelShader)
	{
		m_VertexShader = modelShader.GetVertexShader();
		m_PixelShader = modelShader.GetPixelShader();
		m_Layout = modelShader.GetLayout();
		m_MatrixBuffer = modelShader.GetMatrixBuffer();
		m_ObjectBuffer = modelShader.GetObjectBuffer();
		m_LightBuffer = modelShader.GetLightBuffer();
		m_BlendBuffer = modelShader.GetBlendBuffer();
		m_SampleState = modelShader.GetSampleState();
	}

	return *this;
}

ModelShader::ModelShader(const ModelShader &&modelShader) : m_VertexShader(modelShader.GetVertexShader()), m_PixelShader(modelShader.GetPixelShader()), m_Layout(modelShader.GetLayout()), m_MatrixBuffer(modelShader.GetMatrixBuffer()), m_ObjectBuffer(modelShader.GetObjectBuffer()), m_LightBuffer(modelShader.GetLightBuffer()), m_BlendBuffer(modelShader.GetBlendBuffer()), m_SampleState(modelShader.GetSampleState())
{

}

ModelShader & ModelShader::operator = (const ModelShader &&modelShader)
{
	if (this != &modelShader)
	{
		m_VertexShader = modelShader.GetVertexShader();
		m_PixelShader = modelShader.GetPixelShader();
		m_Layout = modelShader.GetLayout();
		m_MatrixBuffer = modelShader.GetMatrixBuffer();
		m_ObjectBuffer = modelShader.GetObjectBuffer();
		m_LightBuffer = modelShader.GetLightBuffer();
		m_BlendBuffer = modelShader.GetBlendBuffer();
		m_SampleState = modelShader.GetSampleState();
	}

	return *this;
}

ModelShader::~ModelShader()
{
	try
	{
		// Shutdown the vertex and pixel shaders as well as the related objects.
		// Release the sampler state.
		m_SampleState->Release();

		// Release the matrix constant buffer.
		m_MatrixBuffer->Release();

		// Release the object constant buffer.
		m_ObjectBuffer->Release();

		// Release the light constant buffer.
		m_LightBuffer->Release();

		m_BlendBuffer->Release();

		// Release the layout.
		m_Layout->Release();

		// Release the pixel shader.
		m_PixelShader->Release();

		// Release the vertex shader.
		m_VertexShader->Release();
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

bool ModelShader::Render(ID3D11DeviceContext * const deviceContext, const int indexCount, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, ID3D11ShaderResourceView * const * const textureArray, const Light * const light, const XMFLOAT3 &viewPosition, const XMFLOAT4 &objectColour, const float reflectivity, const float objectType, const float objectState, const float renderState, const float timeElapsed, const float timeOffset, const float blendAmount) const
{
	XMMATRIX temporaryWorldMatrix = worldMatrix;
	XMMATRIX temporaryViewMatrix = viewMatrix;
	XMMATRIX temporaryProjectionMatrix = projectionMatrix;

	// Set the shader parameters that it will use for rendering.
	// Transpose the matrices to prepare them for the shader.
	temporaryWorldMatrix = XMMatrixTranspose(temporaryWorldMatrix);
	temporaryViewMatrix = XMMatrixTranspose(temporaryViewMatrix);
	temporaryProjectionMatrix = XMMatrixTranspose(temporaryProjectionMatrix);

	D3D11_MAPPED_SUBRESOURCE mappedResource =
	{

	};

	// Lock the constant buffer so it can be written to.
	deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	MatrixBuffer * const matrixBufferPointer = reinterpret_cast<MatrixBuffer *>(mappedResource.pData);

	// Copy the matrices into the constant buffer.
	matrixBufferPointer->World = temporaryWorldMatrix;
	matrixBufferPointer->View = temporaryViewMatrix;
	matrixBufferPointer->Projection = temporaryProjectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_MatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	int bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);

	deviceContext->Map(m_ObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ObjectBuffer * const objectBufferPointer = reinterpret_cast<ObjectBuffer *>(mappedResource.pData);

	objectBufferPointer->ViewPosition = viewPosition;
	objectBufferPointer->ObjectType = objectType;
	objectBufferPointer->ObjectState = objectState;
	objectBufferPointer->RenderState = renderState;
	objectBufferPointer->TimeElapsed = timeElapsed;
	objectBufferPointer->TimeOffset = timeOffset;

	deviceContext->Unmap(m_ObjectBuffer, 0);

	bufferNumber = 1;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_ObjectBuffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 3, textureArray);

	deviceContext->Map(m_LightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	LightBuffer * const lightBufferPointer = reinterpret_cast<LightBuffer *>(mappedResource.pData);

	lightBufferPointer->LightPosition[0] = light[0].GetPosition();
	lightBufferPointer->AmbientColour[0] = light[0].GetAmbientColour();
	lightBufferPointer->DiffuseColour[0] = light[0].GetDiffuseColour();
	lightBufferPointer->SpecularColour[0] = light[0].GetSpecularColour();

	lightBufferPointer->LightPosition[1] = light[1].GetPosition();
	lightBufferPointer->AmbientColour[1] = light[1].GetAmbientColour();
	lightBufferPointer->DiffuseColour[1] = light[1].GetDiffuseColour();
	lightBufferPointer->SpecularColour[1] = light[1].GetSpecularColour();

	lightBufferPointer->LightPosition[2] = light[2].GetPosition();
	lightBufferPointer->AmbientColour[2] = light[2].GetAmbientColour();
	lightBufferPointer->DiffuseColour[2] = light[2].GetDiffuseColour();
	lightBufferPointer->SpecularColour[2] = light[2].GetSpecularColour();

	lightBufferPointer->ObjectColour = objectColour;
	lightBufferPointer->Reflectivity = reflectivity;
	lightBufferPointer->LightBufferPadding = XMFLOAT3(0.0f, 0.0f, 0.0f);

	deviceContext->Unmap(m_LightBuffer, 0);

	bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_LightBuffer);

	deviceContext->Map(m_BlendBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	BlendBuffer * const blendBufferPointer = reinterpret_cast<BlendBuffer *>(mappedResource.pData);

	blendBufferPointer->BlendAmount = blendAmount;
	blendBufferPointer->BlendBufferPadding = XMFLOAT3(0.0f, 0.0f, 0.0f);

	deviceContext->Unmap(m_BlendBuffer, 0);

	bufferNumber = 1;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_BlendBuffer);

	// Now render the prepared buffers with the shader.
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_Layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_VertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_PixelShader, nullptr, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_SampleState);

	// Render the triangle.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return true;
}