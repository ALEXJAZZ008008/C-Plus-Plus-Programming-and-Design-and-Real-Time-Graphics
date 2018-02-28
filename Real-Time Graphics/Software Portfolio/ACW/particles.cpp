#include "particles.h"

Particles::Particles() : m_Particles(), m_ParticlesShader(nullptr), m_ParticlesVertices(nullptr), m_TextureArray(nullptr), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_Rotation(0.0f), m_Acceleration(0.0f), m_Velocity(0.0f), m_VelocityVariation(0.0f), m_Size(0.0f), m_SpawnRate(0.0f), m_Time(0.0f), m_Count(0), m_MaxNumberOfParticles(0)
{

}

Particles::Particles(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, const char * const textureFilename) : m_Particles(), m_ParticlesShader(new ParticlesShader(device)), m_ParticlesVertices(nullptr), m_TextureArray(new TextureArray(device, deviceContext, textureFilename, textureFilename, textureFilename)), m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_Rotation(0.0f), m_Acceleration(-0.5f), m_Velocity(0.25f), m_VelocityVariation(0.25f), m_Size(0.005f), m_SpawnRate(0.005f), m_Time(0.0f), m_Count(0), m_MaxNumberOfParticles(5000)
{
	m_Count = m_MaxNumberOfParticles * 3;

	m_ParticlesVertices = new ParticleVertex[m_Count];

	long * const indices = new long[m_Count];

	for (int i = 0; i < m_Count; i++)
	{
		indices[i] = i;
	}

	D3D11_BUFFER_DESC vertexBufferDesc =
	{

	};

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(ParticleVertex) * m_Count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData =
	{

	};

	vertexData.pSysMem = m_ParticlesVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc =
	{

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

	delete[] indices;
}

Particles::Particles(const Particles &particles) : m_Particles(particles.GetParticles()), m_ParticlesShader(const_cast<ParticlesShader *>(particles.GetParticlesShader())), m_ParticlesVertices(const_cast<ParticleVertex *>(particles.GetParticlesVertices())), m_TextureArray(const_cast<TextureArray *>(particles.GetTextureArray())), m_VertexBuffer(const_cast<ID3D11Buffer *>(particles.GetVertexBuffer())), m_IndexBuffer(const_cast<ID3D11Buffer *>(particles.GetIndexBuffer())), m_Rotation(particles.GetRotation()), m_Acceleration(particles.GetAcceleration()), m_Velocity(particles.GetVelocity()), m_VelocityVariation(particles.GetVelocityVariation()), m_Size(particles.GetSize()), m_SpawnRate(particles.GetSpawnRate()), m_Time(particles.GetTime()), m_Count(particles.GetCount()), m_MaxNumberOfParticles(particles.GetMaxNumberOfParticles())
{

}

Particles & Particles::operator = (const Particles &particles)
{
	if (this != &particles)
	{
		m_Particles = particles.GetParticles();

		m_ParticlesShader = const_cast<ParticlesShader *>(particles.GetParticlesShader());
		m_ParticlesVertices = const_cast<ParticleVertex *>(particles.GetParticlesVertices());
		m_TextureArray = const_cast<TextureArray *>(particles.GetTextureArray());
		m_VertexBuffer = const_cast<ID3D11Buffer *>(particles.GetVertexBuffer());
		m_IndexBuffer = const_cast<ID3D11Buffer *>(particles.GetIndexBuffer());

		m_Rotation = particles.GetRotation();
		m_Acceleration = particles.GetAcceleration();
		m_Velocity = particles.GetVelocity();
		m_VelocityVariation = particles.GetVelocityVariation();
		m_Size = particles.GetSize();
		m_SpawnRate = particles.GetSpawnRate();
		m_Time = particles.GetTime();

		m_Count = particles.GetCount();
		m_MaxNumberOfParticles = particles.GetMaxNumberOfParticles();
	}

	return *this;
}

Particles::Particles(const Particles &&particles) : m_Particles(particles.GetParticles()), m_ParticlesShader(const_cast<ParticlesShader *>(particles.GetParticlesShader())), m_ParticlesVertices(const_cast<ParticleVertex *>(particles.GetParticlesVertices())), m_TextureArray(const_cast<TextureArray *>(particles.GetTextureArray())), m_VertexBuffer(const_cast<ID3D11Buffer *>(particles.GetVertexBuffer())), m_IndexBuffer(const_cast<ID3D11Buffer *>(particles.GetIndexBuffer())), m_Rotation(particles.GetRotation()), m_Acceleration(particles.GetAcceleration()), m_Velocity(particles.GetVelocity()), m_VelocityVariation(particles.GetVelocityVariation()), m_Size(particles.GetSize()), m_SpawnRate(particles.GetSpawnRate()), m_Time(particles.GetTime()), m_Count(particles.GetCount()), m_MaxNumberOfParticles(particles.GetMaxNumberOfParticles())
{

}

Particles & Particles::operator = (const Particles &&particles)
{
	if (this != &particles)
	{
		m_Particles = particles.GetParticles();

		m_ParticlesShader = const_cast<ParticlesShader *>(particles.GetParticlesShader());
		m_ParticlesVertices = const_cast<ParticleVertex *>(particles.GetParticlesVertices());
		m_TextureArray = const_cast<TextureArray *>(particles.GetTextureArray());
		m_VertexBuffer = const_cast<ID3D11Buffer *>(particles.GetVertexBuffer());
		m_IndexBuffer = const_cast<ID3D11Buffer *>(particles.GetIndexBuffer());

		m_Rotation = particles.GetRotation();
		m_Acceleration = particles.GetAcceleration();
		m_Velocity = particles.GetVelocity();
		m_VelocityVariation = particles.GetVelocityVariation();
		m_Size = particles.GetSize();
		m_SpawnRate = particles.GetSpawnRate();
		m_Time = particles.GetTime();

		m_Count = particles.GetCount();
		m_MaxNumberOfParticles = particles.GetMaxNumberOfParticles();
	}

	return *this;
}

Particles::~Particles()
{
	try
	{
		delete m_ParticlesShader;
		delete[] m_ParticlesVertices;
		delete m_TextureArray;

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

void Particles::Update(ID3D11DeviceContext * const deviceContext, const XMFLOAT3 &position, const XMFLOAT3 &cameraPosition, const bool flyingBool, const float dt)
{
	m_Time += dt;

	m_Rotation = atan2f(position.x - cameraPosition.x, position.z - cameraPosition.z);

	// Insert new particle
	if (flyingBool && m_Time > m_SpawnRate && m_Particles.size() < m_MaxNumberOfParticles - 1)
	{
		m_Time = 0.0f;

		random_device randomDevice;
		mt19937 mt(randomDevice());
		const uniform_real_distribution<float> random(-1.0f, 1.0f);

		Particle temporaryParticle = Particle();

		temporaryParticle.SetPosition(XMFLOAT3(random(mt) + position.x, fabs(random(mt)), random(mt) + position.z));
		temporaryParticle.SetVelocity(XMFLOAT3((random(mt) * m_VelocityVariation), m_Velocity + (random(mt) * m_VelocityVariation), 0.0f));

		int index = 0;

		if (m_Particles.size() > 0)
		{
			while (true)
			{
				if (index == m_Particles.size() || m_Particles.at(index).GetPosition().z < temporaryParticle.GetPosition().z)
				{
					break;
				}
				else
				{
					index++;
				}
			}

			m_Particles.insert(m_Particles.begin() + index, Particle(temporaryParticle.GetPosition(), temporaryParticle.GetVelocity()));
		}
		else
		{
			m_Particles.push_back(Particle(temporaryParticle.GetPosition(), temporaryParticle.GetVelocity()));
		}
	}

	// Update all particles
	for (int i = 0; i < m_Particles.size(); i++)
	{
		m_Particles.at(i).SetVelocity(XMFLOAT3(m_Particles.at(i).GetVelocity().x, m_Particles.at(i).GetVelocity().y + (m_Acceleration * dt), m_Particles.at(i).GetVelocity().z));
		m_Particles.at(i).SetPosition(XMFLOAT3(m_Particles.at(i).GetPosition().x + (m_Particles.at(i).GetVelocity().x * dt), m_Particles.at(i).GetPosition().y + (m_Particles.at(i).GetVelocity().y * dt), m_Particles.at(i).GetPosition().z + (m_Particles.at(i).GetVelocity().z * dt)));
	}

	// Kill particle if it goes below a threashold
	for (int i = 0; i < m_Particles.size(); i++)
	{
		if (m_Particles.at(i).GetPosition().y < 0.0f)
		{
			m_Particles.erase(m_Particles.begin() + i);

			i--;
		}
	}

	memset(m_ParticlesVertices, 0, sizeof(m_ParticlesVertices) * m_Count);

	// Rebuild vertex buffer
	int index = 0;

	for (int i = 0; i < m_Particles.size(); i++)
	{
		m_ParticlesVertices[index].SetPosition(m_Particles.at(i).GetPosition().x - m_Size, m_Particles.at(i).GetPosition().y - m_Size, m_Particles.at(i).GetPosition().z);
		m_ParticlesVertices[index].SetTexture(1.0f, 0.0f);

		index++;

		m_ParticlesVertices[index].SetPosition(m_Particles.at(i).GetPosition().x - (m_Size / 2), m_Particles.at(i).GetPosition().y + m_Size, m_Particles.at(i).GetPosition().z);
		m_ParticlesVertices[index].SetTexture(1.0f, 1.0f);

		index++;

		m_ParticlesVertices[index].SetPosition(m_Particles.at(i).GetPosition().x + m_Size, m_Particles.at(i).GetPosition().y - m_Size, m_Particles.at(i).GetPosition().z);
		m_ParticlesVertices[index].SetTexture(0.0f, 1.0f);

		index++;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource =
	{

	};

	deviceContext->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ParticleVertex * const particleVertexPointer = reinterpret_cast<ParticleVertex *>(mappedResource.pData);

	memcpy(particleVertexPointer, reinterpret_cast<void *>(m_ParticlesVertices), sizeof(ParticleVertex) * m_MaxNumberOfParticles);

	deviceContext->Unmap(m_VertexBuffer, 0);
}

void Particles::Render(ID3D11DeviceContext * const deviceContext, const XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix, const float renderState) const
{
	const unsigned int stride = sizeof(ParticleVertex);
	const unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMMATRIX temporaryWorldMatrix = (worldMatrix * XMMatrixRotationY(m_Rotation));

	m_ParticlesShader->Render(deviceContext, m_Count, temporaryWorldMatrix, viewMatrix, projectionMatrix, m_TextureArray->GetTextureViews().at(0), renderState);
}