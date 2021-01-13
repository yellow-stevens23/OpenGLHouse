#include "Shader.h"

Shader::Shader()
{
	shaderProgramme = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::useShaderProgramme()
{
	glUseProgram(shaderProgramme);
}

bool Shader::readFile(const char* pFileName, string& outFile)
{
	ifstream file(pFileName);
    
	bool ret = false;
    
	if (file.is_open()) 
	{
		string line;
		while (getline(file, line)) 
		{
			outFile.append(line);
			outFile.append("\n");
		}
        
		file.close();
        
		ret = true;
	}
    
	else 
	{
		fprintf(stderr, "Error: cannot open'%s'\n", pFileName);
	}
    
	return ret;
}

void Shader::addShader(GLuint shaderProgramme, const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if (!shaderObj)
	{
		fprintf(stderr, "Error creating shader type: %d\n", shaderType);
		exit(0);
	}
	
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint lengths[1];
	lengths[0] = strlen(pShaderText);
	glShaderSource(shaderObj, 1, p, lengths);
	
	glCompileShader(shaderObj);
	
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObj, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, infoLog);
		exit(1);
	}
	glAttachShader(shaderProgramme, shaderObj);
}

void Shader::compileShader(const char* pVSFilename, const char* pFSFilename)
{
	shaderProgramme = glCreateProgram();
	if (!shaderProgramme)
	{
		 fprintf(stderr, "Error creating shader program\n");
		 exit(1);
		 
	}
	
	string vs, fs;
	
	if (!readFile(pVSFilename, vs))
	{
		exit(1);
	}
	
	if (!readFile(pFSFilename, fs))
	{
		exit(1);
	}
	
	addShader(shaderProgramme, vs.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgramme, fs.c_str(), GL_FRAGMENT_SHADER);
	
	GLint success;
	GLchar errorLog[1024] = { 0 };
	
	glLinkProgram(shaderProgramme);
	glGetProgramiv(shaderProgramme, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramme, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader programme: '%s'\n", errorLog);
		exit(1);
	}
	
	glValidateProgram(shaderProgramme);
	glGetProgramiv(shaderProgramme, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramme, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Invalid shader programme: '%s'\n", errorLog);
		exit(1);
	}
	
	uniformModel = glGetUniformLocation(shaderProgramme, "model");
	uniformProjection = glGetUniformLocation(shaderProgramme, "projection");
	uniformView = glGetUniformLocation(shaderProgramme, "view");
}

GLuint Shader::getProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::getModelLocation()
{
	return uniformModel;
}

GLuint Shader::getViewLocation()
{
	return uniformView;
}

GLuint Shader::getShaderID()
{
	return shaderProgramme;
}

void Shader::clearShaderProgramme()
{
	glUseProgram(0);
}

void Shader::deleteShaderProgramme()
{
	if (shaderProgramme != 0)
	{
		glDeleteProgram(shaderProgramme);
		shaderProgramme = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader()
{
	deleteShaderProgramme();
}
