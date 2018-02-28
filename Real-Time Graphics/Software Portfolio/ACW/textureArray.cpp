#include "textureArray.h"

TextureArray::TextureArray() : m_Texture(nullptr), m_TextureViews(), m_TGAs()
{

}

TextureArray::TextureArray(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, const char * const fileName1, const char * const fileName2, const char * const fileName3) : m_Texture(nullptr), m_TextureViews(), m_TGAs()
{
	LoadTexture(device, deviceContext, 0, fileName1);

	LoadTexture(device, deviceContext, 1, fileName2);

	LoadTexture(device, deviceContext, 2, fileName3);
}

TextureArray::TextureArray(const TextureArray &textureArray) : m_Texture(textureArray.GetTexture()), m_TextureViews(textureArray.GetTextureViews()), m_TGAs(textureArray.GetTGAs())
{

}

TextureArray & TextureArray::operator = (const TextureArray &textureArray)
{
	if (this != &textureArray)
	{
		m_Texture = textureArray.GetTexture();
		m_TextureViews = textureArray.GetTextureViews();
		m_TGAs = textureArray.GetTGAs();
	}

	return *this;
}

TextureArray::TextureArray(const TextureArray &&textureArray) : m_Texture(textureArray.GetTexture()), m_TextureViews(textureArray.GetTextureViews()), m_TGAs(textureArray.GetTGAs())
{

}

TextureArray & TextureArray::operator = (const TextureArray &&textureArray)
{
	if (this != &textureArray)
	{
		m_Texture = textureArray.GetTexture();
		m_TextureViews = textureArray.GetTextureViews();
		m_TGAs = textureArray.GetTGAs();
	}

	return *this;
}

TextureArray::~TextureArray()
{
	try
	{
		// Release the texture view resource.
		for (int i = 0; i < m_TextureViews.size(); i++)
		{
			m_TextureViews[i]->Release();
		}

		// Release the texture.
		m_Texture->Release();

		// Release the TGA data.
		for (int i = 0; i < m_TGAs.size(); i++)
		{
			delete[] m_TGAs[i];
		}
	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}

void TextureArray::LoadTexture(ID3D11Device * const device, ID3D11DeviceContext * const deviceContext, int index, const char * const fileName)
{
	// Load the TGA image data into memory.
	FILE *filePointer = nullptr;

	// Open the TGA file for reading in binary.
	fopen_s(&filePointer, fileName, "rb");

	TGA tga =
	{

	};

	// Read in the file header.
	fread(&tga, sizeof(TGA), 1, filePointer);

	// Get the important information from the header.
	int const height = static_cast<int>(tga.GetHeight());
	int const width = static_cast<int>(tga.GetWidth());

	// Calculate the size of the 32 bit image data.
	int const imageSize = (width * height) * 4;

	// Allocate memory for the TGA image data.
	char * const tgaImage = new char[imageSize];

	// Read in the TGA image data.
	fread(tgaImage, 1, imageSize, filePointer);

	// Close the file.
	fclose(filePointer);

	// Allocate memory for the TGA destination data.
	m_TGAs[index] = new char[imageSize];

	// Initialize the index into the TGA destination data array.
	int tgaDataIndex = 0;

	// Initialize the index into the TGA image data.
	int tgaImageIndex = ((width * height) * 4) - (width * 4);

	// Now copy the TGA image data into the TGA destination array in the correct order since the TGA format is stored upside down.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_TGAs[index][tgaDataIndex + 0] = tgaImage[tgaImageIndex + 2];  // Red.
			m_TGAs[index][tgaDataIndex + 1] = tgaImage[tgaImageIndex + 1];  // Green.
			m_TGAs[index][tgaDataIndex + 2] = tgaImage[tgaImageIndex + 0];  // Blue
			m_TGAs[index][tgaDataIndex + 3] = tgaImage[tgaImageIndex + 3];  // Alpha

			tgaImageIndex += 4;												// Increment the indexes into the TGA data.
			tgaDataIndex += 4;
		}

		// Set the TGA image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		tgaImageIndex -= (width * 8);
	}

	// Release the TGA image data now that it was copied into the destination array.
	delete[] tgaImage;

	D3D11_TEXTURE2D_DESC textureDesc =
	{
		sizeof(textureDesc)
	};

	// Setup the description of the texture.
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture.
	device->CreateTexture2D(&textureDesc, nullptr, &m_Texture);

	// Set the row pitch of the TGA image data.
	int const rowPitch = (width * 4) * sizeof(char);

	// Copy the TGA image data into the texture.
	deviceContext->UpdateSubresource(m_Texture, 0, nullptr, m_TGAs[index], rowPitch, 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourcViewDesc =
	{

	};

	// Setup the shader resource view description.
	shaderResourcViewDesc.Format = textureDesc.Format;
	shaderResourcViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourcViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourcViewDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture.
	device->CreateShaderResourceView(m_Texture, &shaderResourcViewDesc, &m_TextureViews[index]);

	// Generate mipmaps for this texture.
	deviceContext->GenerateMips(m_TextureViews[index]);
}