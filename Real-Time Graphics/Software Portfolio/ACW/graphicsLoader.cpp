#include "graphicsLoader.h"

GraphicsLoader::GraphicsLoader() : m_View(new View(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f))), m_Models(), m_Light(new Light[3]), m_Path()
{
	
}

GraphicsLoader::GraphicsLoader(const char * const graphicsFilename) : m_View(new View(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f))), m_Models(), m_Light(new Light[3]), m_Path()
{
	LoadGraphics(graphicsFilename);
}

GraphicsLoader::GraphicsLoader(const GraphicsLoader &graphicsLoader) : m_View(const_cast<View *>(graphicsLoader.GetView())), m_Models(graphicsLoader.GetModels()), m_Light(const_cast<Light *>(graphicsLoader.GetLight())), m_Path(graphicsLoader.GetPath())
{
	
}

GraphicsLoader & GraphicsLoader::operator = (const GraphicsLoader &graphicsLoader)
{
	if (this != &graphicsLoader)
	{
		m_View = const_cast<View *>(graphicsLoader.GetView());
		m_Models = graphicsLoader.GetModels();
		m_Light = const_cast<Light *>(graphicsLoader.GetLight());
		m_Path = graphicsLoader.GetPath();
	}

	return *this;
}

GraphicsLoader::GraphicsLoader(const GraphicsLoader &&graphicsLoader) : m_View(const_cast<View *>(graphicsLoader.GetView())), m_Models(graphicsLoader.GetModels()), m_Light(const_cast<Light *>(graphicsLoader.GetLight())), m_Path(graphicsLoader.GetPath())
{

}

GraphicsLoader & GraphicsLoader::operator = (const GraphicsLoader &&graphicsLoader)
{
	if (this != &graphicsLoader)
	{
		m_View = const_cast<View *>(graphicsLoader.GetView());
		m_Models = graphicsLoader.GetModels();
		m_Light = const_cast<Light *>(graphicsLoader.GetLight());
		m_Path = graphicsLoader.GetPath();
	}

	return *this;
}

GraphicsLoader::~GraphicsLoader()
{
	try
	{
		delete[] m_Light;

		for (int i = 0; i < m_Path.size(); i++)
		{
			delete m_Path.at(i);
		}

		// Release the model object.
		for (int i = 0; i < m_Models.size(); i++)
		{
			delete m_Models.at(i);
		}

		// Release the camera object.
		delete m_View;
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void GraphicsLoader::LoadGraphics(const char * const graphicsFilename)
{
	ifstream fileStream =
	{

	};

	fileStream.open(graphicsFilename);

	char input = ' ';

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream.get(input);
	fileStream.get(input);

	float viewX, viewY, viewZ;

	fileStream >> viewX >> viewY >> viewZ;

	m_View->SetOutsidePosition(viewX, viewY, viewZ);

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream.get(input);
	fileStream.get(input);

	fileStream >> viewX >> viewY >> viewZ;

	m_View->SetInsidePosition(viewX, viewY, viewZ);

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream.get(input);
	fileStream.get(input);

	fileStream >> viewX >> viewY >> viewZ;

	m_View->SetOutsideRotation(viewX, viewY, viewZ);

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream.get(input);
	fileStream.get(input);

	fileStream >> viewX >> viewY >> viewZ;

	m_View->SetInsideRotation(viewX, viewY, viewZ);

	// Set the initial position of the camera.
	m_View->SetViewToOutside();
	m_View->Render();

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	int count = 0;

	fileStream >> count;

	array<char, 2> inputString =
	{

	};

	inputString.at(1) = '\0';

	array<char, 128> meshFilename =
	{

	};

	array<char, 128> textureFilename =
	{

	};

	array<char, 128> bumpMapFilename =
	{

	};

	array<char, 128> specularMapFilename =
	{

	};

	float meshColourR, meshColourG, meshColourB, meshColourA, meshSizeX, meshSizeY, meshSizeZ, meshPositionX, meshPositionY, meshPositionZ, meshRotationX, meshRotationY, meshRotationZ, meshReflectivity, meshBlendAmount;

	for (int i = 0; i < count; i++)
	{
		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			inputString.at(0) = input;

			strcat_s(meshFilename.data(), meshFilename.size(), inputString.data());

			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			inputString.at(0) = input;

			strcat_s(textureFilename.data(), textureFilename.size(), inputString.data());

			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			inputString.at(0) = input;

			strcat_s(bumpMapFilename.data(), bumpMapFilename.size(), inputString.data());

			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != '"')
		{
			inputString.at(0) = input;

			strcat_s(specularMapFilename.data(), specularMapFilename.size(), inputString.data());

			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> meshColourR >> meshColourG >> meshColourB >> meshColourA;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> meshSizeX >> meshSizeY >> meshSizeZ;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> meshPositionX >> meshPositionY >> meshPositionZ;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> meshRotationX >> meshRotationY >> meshRotationZ;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> meshReflectivity;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> meshBlendAmount;

		m_Models.push_back(new Model(meshFilename.data(), textureFilename.data(), bumpMapFilename.data(), specularMapFilename.data(), XMFLOAT4(meshColourR, meshColourG, meshColourB, meshColourA), XMFLOAT3(meshSizeX, meshSizeY, meshSizeZ), XMFLOAT3(meshPositionX, meshPositionY, meshPositionZ), XMFLOAT3(meshRotationX, meshRotationY, meshRotationZ), static_cast<float>(i), meshReflectivity, meshBlendAmount));
	
		meshFilename =
		{

		};

		textureFilename =
		{

		};

		bumpMapFilename =
		{

		};

		specularMapFilename =
		{

		};
	}

	float lightX, lightY, lightZ, lightW;

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	for (int i = 0; i < 3; i++)
	{
		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ >> lightW;

		m_Light[i].SetPosition(lightX, lightY, lightZ, lightW);

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ >> lightW;

		m_Light[i].SetAmbientColour(lightX, lightY, lightZ, lightW);

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ >> lightW;

		m_Light[i].SetDiffuseColour(lightX, lightY, lightZ, lightW);

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ >> lightW;

		m_Light[i].SetSpecularColour(lightX, lightY, lightZ, lightW);

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ;

		m_Light[i].GetPath().at(0)->x = lightX;
		m_Light[i].GetPath().at(0)->y = lightY;
		m_Light[i].GetPath().at(0)->z = lightZ;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ;

		m_Light[i].GetPath().at(1)->x = lightX;
		m_Light[i].GetPath().at(1)->y = lightY;
		m_Light[i].GetPath().at(1)->z = lightZ;

		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream.get(input);
		fileStream.get(input);

		fileStream >> lightX >> lightY >> lightZ;

		m_Light[i].GetPath().at(2)->x = lightX;
		m_Light[i].GetPath().at(2)->y = lightY;
		m_Light[i].GetPath().at(2)->z = lightZ;
	}

	fileStream.get(input);

	while (input != ':')
	{
		fileStream.get(input);
	}

	fileStream >> count;

	float pathX, pathY, pathZ;

	for (int i = 0; i < count; i++)
	{
		fileStream.get(input);

		while (input != ':')
		{
			fileStream.get(input);
		}

		fileStream >> pathX >> pathY >> pathZ;

		m_Path.push_back(new XMFLOAT3(pathX, pathY, pathZ));
	}

	fileStream.close();
}