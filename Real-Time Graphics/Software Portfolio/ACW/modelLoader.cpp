#include "modelLoader.h"

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

void ModelLoader::LoadModel(ModelVertex *&vertices, long *&indices, int &count) const
{
	count = 3;

	vertices = new ModelVertex[count];
	indices = new long[count];

	vertices[0].SetPosition(-1.0f, -1.0f, 0.0f);
	vertices[0].SetTexture(0.0f, 1.0f);
	vertices[0].SetNormal(0.0f, 0.0f, -1.0f);

	vertices[1].SetPosition(0.0f, 1.0f, 0.0f);
	vertices[1].SetTexture(0.5f, 0.0f);
	vertices[1].SetNormal(0.0f, 0.0f, -1.0f);

	vertices[2].SetPosition(1.0f, -1.0f, 0.0f);
	vertices[2].SetTexture(1.0f, 1.0f);
	vertices[2].SetNormal(0.0f, 0.0f, -1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	NormaliseModel(vertices, count, XMFLOAT3(1.0f, 1.0f, 1.0f));

	CalculateLightingVertices(vertices, count);
}

void ModelLoader::LoadModel(const char * const inputFileName, const char * const outputFileName, ModelVertex *&vertices, long *&indices, int &count, const XMFLOAT3 &size) const
{
	ifstream fileStream =
	{

	};

	fileStream.open(outputFileName);

	if (!fileStream.is_open())
	{
		int vertexCount, textureCount, normalCount, faceCount;

		ReadFile(inputFileName, vertexCount, textureCount, normalCount, faceCount);

		WriteDataStructure(inputFileName, outputFileName, vertexCount, textureCount, normalCount, faceCount);

		fileStream.open(outputFileName);
	}

	char input = ' ';

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream >> count;

	vertices = new ModelVertex[count];
	indices = new long[count];

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream.get(input);
	fileStream.get(input);

	float pX, pY, pZ, tU, tV, nX, nY, nZ;

	for (int i = 0; i < count; i++)
	{
		fileStream >> pX >> pY >> pZ >> tU >> tV >> nX >> nY >> nZ;

		vertices[i].SetPosition(pX, pY, pZ);
		vertices[i].SetTexture(tU, tV);
		vertices[i].SetNormal(nX, nY, nZ);

		indices[i] = i;
	}

	fileStream.close();

	NormaliseModel(vertices, count, size);

	CalculateLightingVertices(vertices, count);
}

void ModelLoader::ReadFile(const char * const fileName, int &vertexCount, int &textureCount, int &normalCount, int &faceCount) const
{
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	ifstream fileStream =
	{

	};

	fileStream.open(fileName);

	char input = ' ';

	fileStream.get(input);

	while (!fileStream.eof())
	{
		if (input == 'v')
		{
			fileStream.get(input);

			if (input == ' ')
			{
				vertexCount++;
			}

			if (input == 't')
			{
				textureCount++;
			}

			if (input == 'n')
			{
				normalCount++;
			}
		}

		if (input == 'f')
		{
			fileStream.get(input);

			if (input == ' ')
			{
				faceCount++;
			}
		}

		while (input != '\n')
		{
			fileStream.get(input);

			if (fileStream.eof())
			{
				break;
			}
		}

		fileStream.get(input);
	}

	fileStream.close();
}

void ModelLoader::WriteDataStructure(const char * const inputFileName, const char * const outputFileName, const int vertexCount, const int textureCount, const int normalCount, const int faceCount) const
{
	ifstream fileStreamIn =
	{

	};

	fileStreamIn.open(inputFileName);

	char input = ' ';

	fileStreamIn.get(input);

	XMFLOAT3 * const vertices = new XMFLOAT3[vertexCount];
	XMFLOAT2 * const textures = new XMFLOAT2[textureCount];
	XMFLOAT3 * const normals = new XMFLOAT3[normalCount];
	Face * const faces = new Face[faceCount];

	int vertexIndex = 0;
	int textureIndex = 0;
	int normalIndex = 0;
	int faceIndex = 0;

	char dump = ' ';

	float pX, pY, pZ, tU, tV, nX, nY, nZ;
	int vIX, vIY, vIZ, tIX, tIY, tIZ, nIX, nIY, nIZ;

	while (!fileStreamIn.eof())
	{
		if (input == 'v')
		{
			fileStreamIn.get(input);

			if (input == ' ')
			{
				fileStreamIn >> pX >> pY >> pZ;

				pZ = -pZ;

				vertices[vertexIndex].x = pX;
				vertices[vertexIndex].y = pY;
				vertices[vertexIndex].z = pZ;

				vertexIndex++;
			}

			if (input == 't')
			{
				fileStreamIn >> tU >> tV;

				tV = -tV;

				textures[textureIndex].x = tU;
				textures[textureIndex].y = tV;

				textureIndex++;
			}

			if (input == 'n')
			{
				fileStreamIn >> nX >> nY >> nZ;

				nZ = -nZ;

				normals[normalIndex].x = nX;
				normals[normalIndex].y = nY;
				normals[normalIndex].z = nZ;

				normalIndex++;
			}
		}

		if (input == 'f')
		{
			fileStreamIn.get(input);

			if (input == ' ')
			{
				fileStreamIn >> vIZ >> dump >> tIZ >> dump >> nIZ >> vIY >> dump >> tIY >> dump >> nIY >> vIX >> dump >> tIX >> dump >> nIX;

				faces[faceIndex].SetVectorIndex(static_cast<float>(vIX), static_cast<float>(vIY), static_cast<float>(vIZ));

				faces[faceIndex].SetTextureIndex(static_cast<float>(tIX), static_cast<float>(tIY), static_cast<float>(tIZ));

				faces[faceIndex].SetNormalIndex(static_cast<float>(nIX), static_cast<float>(nIY), static_cast<float>(nIZ));

				faceIndex++;
			}
		}

		while (input != '\n')
		{
			fileStreamIn.get(input);

			if (fileStreamIn.eof())
			{
				break;
			}
		}

		fileStreamIn.get(input);
	}

	fileStreamIn.close();

	ofstream fileStreamOut =
	{

	};

	fileStreamOut.open(outputFileName);

	fileStreamOut << "Vertex Count: " << (faceCount * 3) << endl;
	fileStreamOut << endl;
	fileStreamOut << "Data:" << endl;
	fileStreamOut << endl;

	int vIndex = 0;
	int tIndex = 0;
	int nIndex = 0;

	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = static_cast<int>(faces[i].GetVectorIndex().x - 1);
		tIndex = static_cast<int>(faces[i].GetTextureIndex().x - 1);
		nIndex = static_cast<int>(faces[i].GetNormalIndex().x - 1);

		fileStreamOut << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' ' << textures[tIndex].x << ' ' << textures[tIndex].y << ' ' << normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = static_cast<int>(faces[i].GetVectorIndex().y - 1);
		tIndex = static_cast<int>(faces[i].GetTextureIndex().y - 1);
		nIndex = static_cast<int>(faces[i].GetNormalIndex().y - 1);

		fileStreamOut << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' ' << textures[tIndex].x << ' ' << textures[tIndex].y << ' ' << normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = static_cast<int>(faces[i].GetVectorIndex().z - 1);
		tIndex = static_cast<int>(faces[i].GetTextureIndex().z - 1);
		nIndex = static_cast<int>(faces[i].GetNormalIndex().z - 1);

		fileStreamOut << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' ' << textures[tIndex].x << ' ' << textures[tIndex].y << ' ' << normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

	delete[] vertices;

	delete[] textures;

	delete[] normals;

	delete[] faces;
}

const float ModelLoader::VertexMagnitude(const XMFLOAT3 &position) const
{
	return sqrt(pow(position.x, 2) + pow(position.y, 2) + pow(position.z, 2));
}

void ModelLoader::NormaliseModel(ModelVertex * const & vertices, const int count, const XMFLOAT3 &size) const
{
	float maxMagnitude = 0.0;
	float currentMagnitude = 0.0;

	for (int i = 0; i < count; i++)
	{
		currentMagnitude = VertexMagnitude(vertices[i].GetPosition());

		if (currentMagnitude > maxMagnitude)
		{
			maxMagnitude = currentMagnitude;
		}
	}

	XMFLOAT3 position =
	{

	};

	for (int i = 0; i < count; i++)
	{
		position = vertices[i].GetPosition();

		position.x /= maxMagnitude;
		position.y /= maxMagnitude;
		position.z /= maxMagnitude;

		position.x *= size.x;
		position.y *= size.y;
		position.z *= size.z;

		vertices[i].SetPosition(position);
	}
}

void ModelLoader::CalculateLightingVertices(ModelVertex * const & vertices, const int count) const
{
	array<ModelVertex, 3> temporaryVertices =
	{

	};

	array<XMFLOAT3, 2> temporaryLightingVertices =
	{

	};

	int index = 0;

	float pX, pY, pZ, tU, tV, nX, nY, nZ;

	for (int i = 0; i < count / 3; i++)
	{
		pX = vertices[index].GetPosition().x;
		pY = vertices[index].GetPosition().y;
		pZ = vertices[index].GetPosition().z;

		tU = vertices[index].GetTexture().x;
		tV = vertices[index].GetTexture().y;

		nX = vertices[index].GetNormal().x;
		nY = vertices[index].GetNormal().y;
		nZ = vertices[index].GetNormal().z;

		temporaryVertices.at(0) = ModelVertex(pX, pY, pZ, tU, tV, nX, nY, nZ);

		index++;

		pX = vertices[index].GetPosition().x;
		pY = vertices[index].GetPosition().y;
		pZ = vertices[index].GetPosition().z;

		tU = vertices[index].GetTexture().x;
		tV = vertices[index].GetTexture().y;

		nX = vertices[index].GetNormal().x;
		nY = vertices[index].GetNormal().y;
		nZ = vertices[index].GetNormal().z;

		temporaryVertices.at(1) = ModelVertex(pX, pY, pZ, tU, tV, nX, nY, nZ);

		index++;

		pX = vertices[index].GetPosition().x;
		pY = vertices[index].GetPosition().y;
		pZ = vertices[index].GetPosition().z;

		tU = vertices[index].GetTexture().x;
		tV = vertices[index].GetTexture().y;

		nX = vertices[index].GetNormal().x;
		nY = vertices[index].GetNormal().y;
		nZ = vertices[index].GetNormal().z;

		temporaryVertices.at(2) = ModelVertex(pX, pY, pZ, tU, tV, nX, nY, nZ);

		index++;

		CalculateTangentBinormal(temporaryVertices.data(), temporaryLightingVertices.data());

		vertices[index - 3].SetTangent(temporaryLightingVertices.at(0).x, temporaryLightingVertices.at(0).y, temporaryLightingVertices.at(0).z);
		vertices[index - 3].SetBinormal(temporaryLightingVertices.at(1).x, temporaryLightingVertices.at(1).y, temporaryLightingVertices.at(1).z);

		vertices[index - 2].SetTangent(temporaryLightingVertices.at(0).x, temporaryLightingVertices.at(0).y, temporaryLightingVertices.at(0).z);
		vertices[index - 2].SetBinormal(temporaryLightingVertices.at(1).x, temporaryLightingVertices.at(1).y, temporaryLightingVertices.at(1).z);

		vertices[index - 1].SetTangent(temporaryLightingVertices.at(0).x, temporaryLightingVertices.at(0).y, temporaryLightingVertices.at(0).z);
		vertices[index - 1].SetBinormal(temporaryLightingVertices.at(1).x, temporaryLightingVertices.at(1).y, temporaryLightingVertices.at(1).z);
	}
}

void ModelLoader::CalculateTangentBinormal(const ModelVertex * const vertices, XMFLOAT3 * const lightingVertices) const
{
	array<XMFLOAT3, 2> temporaryVertices =
	{

	};

	temporaryVertices.at(0) = XMFLOAT3((vertices[1].GetPosition().x - vertices[0].GetPosition().x), (vertices[1].GetPosition().y - vertices[0].GetPosition().y), (vertices[1].GetPosition().z - vertices[0].GetPosition().z));
	temporaryVertices.at(1) = XMFLOAT3((vertices[2].GetPosition().x - vertices[0].GetPosition().x), (vertices[2].GetPosition().y - vertices[0].GetPosition().y), (vertices[2].GetPosition().z - vertices[0].GetPosition().z));

	array<XMFLOAT2, 2> temporaryLightingVertices =
	{

	};

	temporaryLightingVertices.at(0) = XMFLOAT2((vertices[1].GetTexture().x - vertices[0].GetTexture().x), (vertices[1].GetTexture().y - vertices[0].GetTexture().y));
	temporaryLightingVertices.at(1) = XMFLOAT2((vertices[2].GetTexture().x - vertices[0].GetTexture().x), (vertices[2].GetTexture().y - vertices[0].GetTexture().y));

	float const denominator = 1.0f / ((temporaryLightingVertices.at(0).x * temporaryLightingVertices.at(1).y) - (temporaryLightingVertices.at(1).x * temporaryLightingVertices.at(0).y));

	lightingVertices[0] = XMFLOAT3((temporaryLightingVertices.at(1).y * temporaryVertices.at(0).x) - (temporaryLightingVertices.at(0).y * temporaryVertices.at(1).x) * denominator, (temporaryLightingVertices.at(1).y * temporaryVertices.at(0).y) - (temporaryLightingVertices.at(0).y * temporaryVertices.at(1).y) * denominator, (temporaryLightingVertices.at(1).y * temporaryVertices.at(0).z) - (temporaryLightingVertices.at(0).y * temporaryVertices.at(1).z) * denominator);
	lightingVertices[1] = XMFLOAT3((temporaryLightingVertices.at(0).x * temporaryVertices.at(1).x) - (temporaryLightingVertices.at(1).x * temporaryVertices.at(0).x) * denominator, (temporaryLightingVertices.at(0).x * temporaryVertices.at(1).y) - (temporaryLightingVertices.at(1).x * temporaryVertices.at(0).y) * denominator, (temporaryLightingVertices.at(0).x * temporaryVertices.at(1).z) - (temporaryLightingVertices.at(1).x * temporaryVertices.at(0).z) * denominator);

	float length = sqrt(pow(lightingVertices[0].x, 2) + pow(lightingVertices[0].y, 2) + pow(lightingVertices[0].z, 2));

	lightingVertices[0] = XMFLOAT3((lightingVertices[0].x / length), (lightingVertices[0].y / length), (lightingVertices[0].z / length));

	length = sqrt(pow(lightingVertices[1].x, 2) + pow(lightingVertices[1].y, 2) + pow(lightingVertices[1].z, 2));

	lightingVertices[1] = XMFLOAT3((lightingVertices[1].x / length), (lightingVertices[1].y / length), (lightingVertices[1].z / length));
}