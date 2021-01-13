#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <cstdio>
#include <GL/glew.h>

class Texture
{

public:
	Texture(const char* fName);
	bool loadTexture();
	void useTexture();
	void clearTexture();
	~Texture();

private:
	GLuint m_textureID;
	int m_width, m_height, m_numChannels;
	const char* m_filename;
};

#endif
