#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	
	stbi_set_flip_vertically_on_load(true);  
	unsigned char* data = stbi_load(m_filename, &m_width, &m_height, &m_numChannels, 0);
	
	if (!data)
	{
		printf("Whoops! You don't seem to have %s on your hard drive.\n", m_filename);
		return false;
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
	
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
