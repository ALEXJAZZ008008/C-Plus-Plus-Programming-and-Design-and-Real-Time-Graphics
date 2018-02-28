#include "imageShader.h"

ImageShader::ImageShader() : m_VertexShader(nullptr), m_PixelShader(nullptr), m_Layout(nullptr), m_MatrixBuffer(nullptr), m_ImageBuffer(nullptr), m_SampleState(nullptr)
{
	
}

ImageShader::ImageShader(ID3D11Device * const device) : m_VertexShader(nullptr), m_PixelShader(nullptr), m_Layout(nullptr), m_MatrixBuffer(nullptr), m_ImageBuffer(nullptr), m_SampleState(nullptr)
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
	D3DCompileFromFile(L"../ACW/imageVertexShader.hlsl", nullptr, nullptr, "ImageVertexShader", "vs_5_0", shaderFlags, 0, &vertexShaderBuffer, nullptr);

	// Create the vertex shader from the buffer.
	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_VertexShader);

	// Initialize the pixel shader.
	// Initialize the pointers this function will use to null.
	ID3D10Blob *pixelShaderBuffer = nullptr;

	// Compile the pixel shader code.
	D3DCompileFromFile(L"../ACW/imagePixelShader.hlsl", nullptr, nullptr, "ImagePixelShader", "ps_5_0", shaderFlags, 0, &pixelShaderBuffer, nullptr);

	// Create the pixel shader from the buffer.
	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_PixelShader);

	// Create the vertex input layout description.
	// This setup needs to match the VertexType stucture in the Model and in the shader.
	array<D3D11_INPUT_ELEMENT_DESC, 2> layout =
	{

	};

	layout.at(0) =
	{
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	};

	layout.at(1) =
	{
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	};

	// Create the vertex input layout.
	device->CreateInputLayout(layout.data(), static_cast<int>(layout.size()), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_Layout);

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

	D3D11_BUFFER_DESC imageBufferDesc =
	{
		sizeof(imageBufferDesc)
	};

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	imageBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	imageBufferDesc.ByteWidth = sizeof(ImageBuffer);
	imageBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	imageBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	imageBufferDesc.MiscFlags = 0;
	imageBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	device->CreateBuffer(&imageBufferDesc, nullptr, &m_ImageBuffer);

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
}

ImageShader::ImageShader(const ImageShader &imageShader) : m_VertexShader(imageShader.GetVertexShader()), m_PixelShader(imageShader.GetPixelShader()), m_Layout(imageShader.GetLayout()), m_MatrixBuffer(imageShader.GetMatrixBuffer()), m_ImageBuffer(imageShader.GetImageBuffer()), m_SampleState(imageShader.GetSampleState())
{
	
}

ImageShader & ImageShader::operator = (const ImageShader &imageShader)
{
	if (this != &imageShader)
	{
		m_VertexShader = imageShader.GetVertexShader();
		m_PixelShader = imageShader.GetPixelShader();
		m_Layout = imageShader.GetLayout();
		m_MatrixBuffer = imageShader.GetMatrixBuffer();
		m_ImageBuffer = imageShader.GetImageBuffer();
		m_SampleState = imageShader.GetSampleState();
	}

	return *this;
}

ImageShader::ImageShader(const ImageShader &&imageShader) : m_VertexShader(imageShader.GetVertexShader()), m_PixelShader(imageShader.GetPixelShader()), m_Layout(imageShader.GetLayout()), m_MatrixBuffer(imageShader.GetMatrixBuffer()), m_ImageBuffer(imageShader.GetImageBuffer()), m_SampleState(imageShader.GetSampleState())
{

}

ImageShader & ImageShader::operator = (const ImageShader &&imageShader)
{
	if (this != &imageShader)
	{
		m_VertexShader = imageShader.GetVertexShader();
		m_PixelShader = imageShader.GetPixelShader();
		m_Layout = imageShader.GetLayout();
		m_MatrixBuffer = imageShader.GetMatrixBuffer();
		m_ImageBuffer = imageShader.GetImageBuffer();
		m_SampleState = imageShader.GetSampleState();
	}

	return *this;
}

ImageShader::~ImageShader()
{
	try
	{
		// Shutdown the vertex and pixel shaders as well as the related objects.
		// Release the sampler state.
		m_SampleState->Release();

		// Release the matrix constant buffer.
		m_MatrixBuffer->Release();

		m_ImageBuffer->Release();

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

bool ImageShader::Render(ID3D11DeviceContext * const deviceContext, const int indexCount, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix, ID3D11ShaderResourceView * const texture, const XMFLOAT4 &colour) const
{
	// Set the shader parameters that it will use for rendering.
	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	D3D11_MAPPED_SUBRESOURCE mappedResource =
	{

	};

	// Lock the constant buffer so it can be written to.
	deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	MatrixBuffer * const matrixBufferPointer = reinterpret_cast<MatrixBuffer *>(mappedResource.pData);

	// Copy the matrices into the constant buffer.
	matrixBufferPointer->World = worldMatrix;
	matrixBufferPointer->View = viewMatrix;
	matrixBufferPointer->Projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_MatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	int bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);

	deviceContext->PSSetShaderResources(0, 1, &texture);

	deviceContext->Map(m_ImageBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ImageBuffer * const imageBufferPointer = reinterpret_cast<ImageBuffer *>(mappedResource.pData);

	imageBufferPointer->Colour = colour;

	deviceContext->Unmap(m_ImageBuffer, 0);

	bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_ImageBuffer);

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