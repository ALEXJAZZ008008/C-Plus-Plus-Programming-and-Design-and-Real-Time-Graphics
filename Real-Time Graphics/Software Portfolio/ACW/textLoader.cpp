#include "textLoader.h"

TextLoader::TextLoader() : m_Text(nullptr), m_Texture(nullptr)
{

}

TextLoader::TextLoader(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, const char * const textFileName, const char * const textureFileName) : m_Text(nullptr), m_Texture(new TextureArray(device, deviceContext, textureFileName, textureFileName, textureFileName))
{
	int const textSize = 95;

	m_Text = new XMFLOAT3[textSize];

	ifstream fileStream =
	{

	};

	fileStream.open(textFileName);

	char input = ' ';

	float x, y, z;

	for (int i = 0; i < textSize; i++)
	{
		fileStream.get(input);

		while (input != ' ')
		{
			fileStream.get(input);
		}

		fileStream.get(input);

		while (input != ' ')
		{
			fileStream.get(input);
		}

		fileStream >> x >> y >> z;

		m_Text[i].x = x;
		m_Text[i].y = y;
		m_Text[i].z = z;
	}

	fileStream.close();
}

TextLoader::TextLoader(const TextLoader &textLoader) : m_Text(const_cast<XMFLOAT3 *>(textLoader.GetText())), m_Texture(const_cast<TextureArray *>(textLoader.GetTexture()))
{

}

TextLoader & TextLoader::operator = (const TextLoader &textLoader)
{
	if (this != &textLoader)
	{
		m_Text = const_cast<XMFLOAT3 *>(textLoader.GetText());
		m_Texture = const_cast<TextureArray *>(textLoader.GetTexture());
	}

	return *this;
}

TextLoader::TextLoader(const TextLoader &&textLoader) : m_Text(const_cast<XMFLOAT3 *>(textLoader.GetText())), m_Texture(const_cast<TextureArray *>(textLoader.GetTexture()))
{

}

TextLoader & TextLoader::operator = (const TextLoader &&textLoader)
{
	if (this != &textLoader)
	{
		m_Text = const_cast<XMFLOAT3 *>(textLoader.GetText());
		m_Texture = const_cast<TextureArray *>(textLoader.GetTexture());
	}

	return *this;
}

TextLoader::~TextLoader()
{
	try
	{
		delete[] m_Text;
		delete m_Texture;
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void TextLoader::GetVertices(void * const vertices, const char * const input, XMFLOAT2 &position) const
{
	ImageVertex * const verticesPointer = reinterpret_cast<ImageVertex *>(vertices);

	int const verticesSize = static_cast<int>(strlen(input));

	int verticesIndex = 0;

	int text = 0;

	for (int i = 0; i < verticesSize; i++)
	{
		text = static_cast<int>(input[i]) - 32;

		if (text == 0)
		{
			position.x = (position.x + 3.0f);
		}
		else
		{
			verticesPointer[verticesIndex].SetPosition(position.x, position.y, 0.0f);
			verticesPointer[verticesIndex].SetTexture(m_Text[text].x, 0.0f);

			verticesIndex++;

			verticesPointer[verticesIndex].SetPosition(position.x + m_Text[text].z, position.y - 16.0f, 0.0f);
			verticesPointer[verticesIndex].SetTexture(m_Text[text].y, 1.0f);

			verticesIndex++;

			verticesPointer[verticesIndex].SetPosition(position.x, position.y - 16.0f, 0.0f);
			verticesPointer[verticesIndex].SetTexture(m_Text[text].x, 1.0f);

			verticesIndex++;

			verticesPointer[verticesIndex].SetPosition(position.x, position.y, 0.0f);
			verticesPointer[verticesIndex].SetTexture(m_Text[text].x, 0.0f);

			verticesIndex++;

			verticesPointer[verticesIndex].SetPosition(position.x + m_Text[text].z, position.y, 0.0f);
			verticesPointer[verticesIndex].SetTexture(m_Text[text].y, 0.0f);

			verticesIndex++;

			verticesPointer[verticesIndex].SetPosition(position.x + m_Text[text].z, position.y - 16.0f, 0.0f);
			verticesPointer[verticesIndex].SetTexture(m_Text[text].y, 1.0f);

			verticesIndex++;

			position.x = ((position.x + m_Text[text].z) + 1.0f);
		}
	}
}