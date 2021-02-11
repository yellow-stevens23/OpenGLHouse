#include "Texture.h"
#include <iostream>
#include <fstream>

Texture::Texture(const char* fname)
{
	m_filename = fname;
	m_textureID = 0;
	m_height = 0;
	m_width = 0;
	m_numChannels = 0;
}

bool Texture::loadTexture()
{
	float borderColour[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 
	
	#pragma pack(push, 1)	
	
	struct BITMAPFileHeader
	{
		unsigned char fileType1;
		unsigned char fileType2;
		uint32_t imageSize;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t dataOffset; 
		
	};
	
	struct BITMAPInfoHeader
	{
		uint32_t headerSize;
		int32_t width;
		int32_t height;
		uint16_t planes;
		uint16_t bitCount;
		uint32_t compression;
		uint32_t dataSize;
		int32_t horizontalResolution;
		int32_t verticalResolution;
		uint32_t coloursUsed;
		uint32_t importantColours; 
	};
	
	#pragma pack(pop)

	uint8_t* dataBuffer[] = {nullptr, nullptr}; 
	uint8_t* imageData = nullptr; 
	
	BITMAPFileHeader* header;
	BITMAPInfoHeader* info;
	
	std::ifstream file;
	file.open(m_filename, std::ios::binary);
	if (!file)
	{
		std::cout << "Image could not be opened" << std::endl;
		return 1;
	}
	
	dataBuffer[0] = new uint8_t[sizeof(BITMAPFileHeader)];
	dataBuffer[1] = new uint8_t[sizeof(BITMAPInfoHeader)];
	
	file.read((char*)dataBuffer[0], sizeof(BITMAPFileHeader));
	file.read((char*)dataBuffer[1], sizeof(BITMAPInfoHeader));
	
	header = (BITMAPFileHeader*) dataBuffer[0];
	info = (BITMAPInfoHeader*) dataBuffer[1];
	
	if((header->fileType1 != 'B') || (header->fileType2 != 'M'))
	{
		std::cout << "File \"" << m_filename << "\" isn't a bitmap file\n";
		return 1;
	}
	
	imageData = new uint8_t[info->dataSize];

	// Go to where image data starts, then read in image data
	file.seekg(header->dataOffset);
	file.read((char*)imageData, info->dataSize);	
	
	GLenum format;
	int step;

	if(info->bitCount == 32) 
	{
		format = GL_RGBA;
		step = 4;
	}
	else if (info->bitCount == 24)
	{
		format = GL_RGB;
		step = 3;
	}
	else
	{	

		std::cout << "Whoa! How did you load THAT file?" << std::endl;
	}
	
	uint8_t tempRGB = 0;
	for (unsigned long i=0; i < info->dataSize; i += step)
	{
		tempRGB = imageData[i];
		imageData[i] = imageData[i + 2];
		imageData[i+2] = tempRGB;
	} 
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->width, info->height, 0, format, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return true;
}

void Texture::useTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &m_textureID);
	m_textureID = 0;
	m_height = 0;
	m_width = 0;
	m_numChannels = 0;
	m_filename = "";
	
}

Texture::~Texture()
{
	clearTexture();
}
