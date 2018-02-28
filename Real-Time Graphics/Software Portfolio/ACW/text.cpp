#include "text.h"

Text::Text() : m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_Count(0), m_MaximumCount(0), m_Colour()
{

}

Text::Text(ID3D11Device * const device, const int maximumCount) : m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_Count(maximumCount * 6), m_MaximumCount(maximumCount), m_Colour()
{
	ImageVertex * const vertices = new ImageVertex[m_Count];

	long * const indices = new long[m_Count];

	for (int i = 0; i < m_Count; i++)
	{
		indices[i] = i;
	}

	D3D11_BUFFER_DESC vertexBufferDesc =
	{
		sizeof(vertexBufferDesc)
	};

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(ImageVertex) * m_Count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData =
	{

	};

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc =
	{
		sizeof(indexBufferDesc)
	};

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(long) * m_Count;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData =
	{

	};

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);

	delete[] vertices;

	delete[] indices;
}

Text::Text(const Text &text) : m_VertexBuffer(text.GetVertexBuffer()), m_IndexBuffer(text.GetIndexBuffer()), m_Count(text.GetCount()), m_MaximumCount(text.GetMaximumCount()), m_Colour(text.GetColour())
{

}

Text & Text::operator = (const Text &text)
{
	if (this != &text)
	{
		m_VertexBuffer = text.GetVertexBuffer();
		m_IndexBuffer = text.GetIndexBuffer();

		m_Count = text.GetCount();
		m_MaximumCount = text.GetMaximumCount();

		m_Colour = text.GetColour();
	}

	return *this;
}

Text::Text(const Text &&text) : m_VertexBuffer(text.GetVertexBuffer()), m_IndexBuffer(text.GetIndexBuffer()), m_Count(text.GetCount()), m_MaximumCount(text.GetMaximumCount()), m_Colour(text.GetColour())
{

}

Text & Text::operator = (const Text &&text)
{
	if (this != &text)
	{
		m_VertexBuffer = text.GetVertexBuffer();
		m_IndexBuffer = text.GetIndexBuffer();

		m_Count = text.GetCount();
		m_MaximumCount = text.GetMaximumCount();

		m_Colour = text.GetColour();
	}

	return *this;
}

Text::~Text()
{
	try
	{
		m_VertexBuffer->Release();

		m_IndexBuffer->Release();
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void Text::Update(ID3D11DeviceContext * const deviceContext, const TextLoader * const textLoader, const char * const text, const XMFLOAT2 &screen, const XMFLOAT2 &inPosition, const XMFLOAT3 &colour)
{
	m_Colour = colour;

	ImageVertex * const vertices = new ImageVertex[m_Count];

	XMFLOAT2 position =
	{

	};

	position.x = (-static_cast<float>(screen.x / 2) + inPosition.x);
	position.y = (static_cast<float>(screen.y / 2) - inPosition.y);

	textLoader->GetVertices(reinterpret_cast<void *>(vertices), text, position);

	D3D11_MAPPED_SUBRESOURCE mappedResource =
	{

	};

	deviceContext->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ImageVertex * const verticesPointer = reinterpret_cast<ImageVertex *>(mappedResource.pData);

	memcpy(verticesPointer, reinterpret_cast<void *>(vertices), sizeof(ImageVertex) * m_Count);

	deviceContext->Unmap(m_VertexBuffer, 0);

	delete[] vertices;
}

void Text::Render(ID3D11DeviceContext * const deviceContext, const TextLoader * const textLoader, const  ImageShader * const imageShader, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &orthographicMatrix) const
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// Set vertex buffer stride and offset.
	unsigned int const  stride = sizeof(ImageVertex);
	unsigned int const  offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMFLOAT4 const colour = XMFLOAT4(m_Colour.x, m_Colour.y, m_Colour.z, 1.0f);

	imageShader->Render(deviceContext, m_Count, worldMatrix, viewMatrix, orthographicMatrix, textLoader->GetTexture()->GetTextureViews().at(0), colour);
}