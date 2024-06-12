#include "textureclass.h"

TextureClass::TextureClass()
{
	m_targaData = 0;
	m_texture = 0;
	m_textureView = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string filename)
{
	Logger::Get().Log(("Iinitializing texture: %s", filename), __FILE__, __LINE__, Logger::LogLevel::Initialize);

	bool result;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	// Load the targa image data into memory.
	result = LoadTarga(filename);
	if (!result)
	{
		Logger::Get().Log("Failed to load targa data", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}
	// Setup the description of the texture.
	textureDesc.Height = m_height;
	textureDesc.Width = m_width;
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
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
	if (FAILED(hResult))
	{
		Logger::Get().Log("Failed to create texture", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (m_width * 4) * sizeof(unsigned char);
	// Copy the targa image data into the texture.
	deviceContext->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);
	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture.
	hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
	if (FAILED(hResult))
	{
		Logger::Get().Log("Failed to create shader resource view", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Generate mipmaps for this texture.
	deviceContext->GenerateMips(m_textureView);

	// Release the targa image data now that the image data has been loaded into the texture.
	delete[] m_targaData;
	m_targaData = 0;

	Logger::Get().Log("Texture initialized", __FILE__, __LINE__, Logger::LogLevel::Initialize);

	return true;
}

void TextureClass::Shutdown()
{

	Logger::Get().Log("Shutting down texture", __FILE__, __LINE__, Logger::LogLevel::Shutdown);
	// Release the texture view resource.
	if (m_textureView)
	{
		m_textureView->Release();
		m_textureView = 0;
	}

	// Release the texture.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	// Release the targa data.
	if (m_targaData)
	{
		delete[] m_targaData;
		m_targaData = 0;
	}

	Logger::Get().Log("Texture shut down", __FILE__, __LINE__, Logger::LogLevel::Shutdown);

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_textureView;
}

bool TextureClass::LoadTarga(std::string filename)
{

	Logger::Get().Log(("Loading targa file: %s", filename), __FILE__, __LINE__);
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	unsigned char* targaImage;


	// Open the targa file for reading in binary.
	error = fopen_s(&filePtr, filename.c_str(), "rb");
	if (error != 0)
	{
		Logger::Get().Log("Failed to open targa file", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Read in the file header.
	count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		Logger::Get().Log("Failed to read targa file header", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Get the important information from the header.
	m_height = (int)targaFileHeader.height;
	m_width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;

	// Check that it is 32 bit and not 24 bit.
	if (bpp != 32 && bpp != 24)
	{
		Logger::Get().Log("Targa file is not 32 or 24 bit", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Calculate the size of the 32 bit image data.
	imageSize = m_width * m_height * (bpp / 8);

	// Allocate memory for the targa image data.
	targaImage = new unsigned char[imageSize];

	// Read in the targa image data.
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		Logger::Get().Log("Failed to read targa image data", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0)
	{
		Logger::Get().Log("Failed to close targa file", __FILE__, __LINE__, Logger::LogLevel::Error);
		return false;
	}

	// Allocate memory for the targa destination data.
	m_targaData = new unsigned char[imageSize];

	// Initialize the index into the targa destination data array.
	index = 0;

	// Initialize the index into the targa image data.
	k = (m_width * m_height * (bpp / 8)) - (m_width * (bpp / 8));

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down and also is not in RGBA order.
	for (j = 0; j < m_height; j++)
	{
		for (i = 0; i < m_width; i++)
		{
			if (index + 3 < imageSize) // Ajout de la vérification ici
			{
				m_targaData[index + 0] = targaImage[k + 2];  // Red.
				m_targaData[index + 1] = targaImage[k + 1];  // Green.
				m_targaData[index + 2] = targaImage[k + 0];  // Blue
				if (bpp == 32)
				{
					m_targaData[index + 3] = targaImage[k + 3];  // Alpha
				}
			}
			else
			{
				Logger::Get().Log("Index out of bounds", __FILE__, __LINE__, Logger::LogLevel::Error);
				return false;
			}

			// Increment the indexes into the targa data.
			k += (bpp / 8);
			index += (bpp / 8);
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (m_width * (bpp / 8) * 2);
	}


	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = 0;

	Logger::Get().Log(("targa file %s loaded", filename), __FILE__, __LINE__);

	return true;
}


int TextureClass::GetWidth()
{
	return m_width;
}


int TextureClass::GetHeight()
{
	return m_height;
}
