#ifndef SHADER_H_
#define SHADER_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

#include <GL/glew.h>

using namespace std;

class Shader
{
public:
	Shader();
	void compileShader(const char* pVSFilename, const char* pFSFilename);
	void useShaderProgramme();
	void clearShaderProgramme();
	void deleteShaderProgramme();
	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getShaderID();
	
	~Shader();

private:
	bool readFile(const char* pFileName, string& outFile);
	void addShader(GLuint shaderProgramme, const char* pShaderText, GLenum shaderType);
	
	
	GLuint shaderProgramme, uniformProjection, uniformModel, uniformView;
};

#endif
