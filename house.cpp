#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLWindow.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

// couple of namespaces - not everyone likes this. Good practice is not to use namespace but in this project its not a problem.
using namespace std;
using namespace glm;


// the global variables are mostly constants with the exception of the vector which I don't want to be passing back and forth
const float toRadians = 3.141592654f / 180.0f;

// vertex and fragement shader filenames
const char* pVSFilename ="Shaders/shader.ver";
const char* pFSFilename = "Shaders/shader.fra";

vector<Mesh*> meshList;


void createObject()
{
	unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3,
			3, 4, 5,
			3, 5, 6,
			6, 7, 8,
			7, 8, 9,
			10, 11, 12,
			10, 12, 13,
			14, 15, 16,
			15, 16, 17,
			15, 18, 19,
			18, 19, 20,
			20, 21, 22,
			20, 22, 23,
			21, 24, 25, 
			21, 25, 1,
			26, 27, 28,
			26, 28, 29,
			22, 23, 30,
			23, 30, 31,
			0, 2, 32,
			2, 32, 33,
			30, 31, 34,
			31, 34, 35,
			35, 36, 37,
			35, 37, 38,
			38, 33, 32,
			39, 38, 32,
			39, 40, 41,
			41, 39, 34,
			42, 43, 44,
			43, 44, 45,
			46, 47, 48,
			47, 48, 49,
			50, 51, 52,
			51, 52, 53
				};

// note I have used S and T for texture coordinates u and v are often used for these instead. OpenGL uses S and T and so, therefore, do I
// I am using R G B elements to add a bit of shading and colour to the boring texture which are simple photos

	GLfloat vertices[] = 	{
		//	  x     y     z	  r     g    b          s    t
			-0.8f, 0.8f, -0.8,	0.7f, 0.7f, 0.7f,	0.1f, 0.9f,	// 0
			-0.6f, 0.8f, -0.8f,	0.7f, 0.7f, 0.7f,	0.2f, 0.9f,	// 1
			-0.8f, -0.9f, -0.8f,	0.7f, 0.7f, 0.7f,	0.1f, 0.05f, 	// 2
			-0.6f, -0.9f, -0.8f,	0.7f, 0.7f, 0.7f,	0.2f, 0.05f,	// 3
			-0.6f, -0.6f, -0.8f,	0.7f, 0.7f, 0.7f,	0.2f, 0.2f, 	// 4
			-0.2f, -0.6f, -0.8f,	0.7f, 0.7f, 0.7f,	0.4f, 0.2f,	// 5
			-0.2f, -0.9f, -0.8f,	0.7f, 0.7f, 0.7f,	0.4f, 0.05f,	// 6
			-0.4f, -0.6f, -0.8f, 	0.7f, 0.7f, 0.7f,	0.3f, 0.2f,	// 7
			-0.2f, -0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.4f, 0.4f,	// 8
			-0.4f, -0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.3f, 0.4f,	// 9
			-0.6f, -0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.2f, 0.4f,	// 10
			0.6f, -0.2f, -0.8f, 	0.7f, 0.7f, 0.7f,	0.8f, 0.4f,	// 11
			0.6f, 0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.8f, 0.6f,	// 12
			-0.6, 0.2f, -0.8f, 	0.7f, 0.7f, 0.7f,	0.2f, 0.6f,	// 13
			0.2f, -0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.6f, 0.4f,	// 14
			0.2f, -0.6f, -0.8f,	0.7f, 0.7f, 0.7f,	0.6f, 0.2f,	// 15
			0.4f, -0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.7f, 0.4f,	// 16
			0.4f, -0.6f, -0.8f,	0.7f, 0.7f, 0.7f,	0.7f, 0.2f,	// 17
			0.6f, -0.6f, -0.8f,	0.7f, 0.7f, 0.7f,	0.8f, 0.2f,	// 18
			0.2f, -0.9f, -0.8f,	0.7f, 0.7f, 0.7f,	0.6f, 0.05f,	// 19
			0.6f, -0.9f, -0.8f,	0.7f, 0.7f, 0.7f,	0.8f, 0.05f,	// 20
			0.6f, 0.8f, -0.8f,	0.7f, 0.7f, 0.7f,	0.8f, 0.9f,	// 21
			0.8f, 0.8f, -0.8f,	0.7f, 0.7f, 0.7f,	0.9f, 0.9f,	// 22
			0.8f, -0.9f, -0.8f,	0.7f, 0.7f, 0.7f,	0.9f, 0.05f,	// 23
			0.6f, 0.7f, -0.8f,	0.7f, 0.7f, 0.7f,	0.8f, 0.85f,	// 24
			-0.6f, 0.7f, -0.8f,	0.7f, 0.7f, 0.7f,	0.2f, 0.85f,	// 25
			0.2f, 0.7f, -0.8f,	0.7f, 0.7f, 0.7f,	0.6f, 0.85f,	// 26
			0.2f, 0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.6f, 0.6f,	// 27
			-0.2f, 0.2f, -0.8f,	0.7f, 0.7f, 0.7f,	0.4f, 0.6f,	// 28
			-0.2f, 0.7f, -0.8f,	0.7f, 0.7f, 0.7f,	0.4f, 0.85f,	// 29
			0.8f, 0.8f, 0.8f,	0.7f, 0.7f, 0.7f,	0.1f, 0.9f,	// 30
			0.8f, -0.9f, 0.8f,	0.4f, 0.4f, 0.4f,	0.1f, 0.05f,	// 31
			-0.8f, 0.8f, 0.8f,	0.4f, 0.4f, 0.4f,	0.9f, 0.9f,	// 32
			-0.8f, -0.9, 0.8f, 	0.4f, 0.4f, 0.4f,	0.9f, 0.05f,	// 33
			0.6f, 0.8f, 0.8f,	0.4f, 0.4f, 0.4f,	0.2f, 0.9f,	// 34
			0.6f, -0.9f, 0.8f,	0.4f, 0.4f, 0.4f,	0.2f, 0.05f,	// 35
			0.6f, -0.7, 0.8f,	0.4f, 0.4f, 0.4f,	0.2f, 0.15f,	// 36
			-0.6f, -0.7f, 0.8f, 	0.4f, 0.4f, 0.4f,	0.8f, 0.15f,	// 37
			-0.6f, -0.9f, 0.8f,	0.4f, 0.4f, 0.4f,	0.8f, 0.05f,	// 38
			-0.6f, 0.8f, 0.8f, 	0.4f, 0.4f, 0.4f,	0.8f, 0.9f,	// 39
			-0.6f, 0.7f, 0.8f, 	0.4f, 0.4f, 0.4f,	0.8f, 0.85f,	// 40
			0.6f, 0.7f, 0.8f,	0.4f, 0.4f, 0.4f,	0.2f, 0.85f,	// 41
			0.2f, 0.7f, 0.8f,	0.4f, 0.4f, 0.4f,	0.4f, 0.85f,	// 42
			0.2f, -0.7, 0.8f,	0.4f, 0.4f, 0.4f,	0.4f, 0.15f,	// 43
			-0.2f, 0.7f, 0.8f,	0.4f, 0.4f, 0.4f,	0.6f, 0.85f,	// 44
			-0.2f, -0.7f, 0.8f,	0.4f, 0.4f, 0.4f,	0.6f, 0.15f,	// 45
			0.6f, 0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.2f, 0.6f,	// 46
			0.6f, -0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.2f, 0.4f,	// 47
			0.2f, 0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.4f, 0.6f,	// 48
			0.2f, -0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.4f, 0.4f,	// 49
			-0.2f, 0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.6f, 0.6f,	// 50
			-0.2f, -0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.6f, 0.4f,	// 51
			-0.6f, 0.2f, 0.8f, 	0.4f, 0.4f, 0.4f,	0.8f, 0.6f,	// 52
			-0.6f, -0.2f, 0.8f,	0.4f, 0.4f, 0.4f,	0.8f, 0.4f	// 53
		};
	
	unsigned int floorIndices[] = {
		0, 1, 2,
		1, 2, 3
	};
	
	GLfloat floorVertices[] = {
	//	   x     y    z  		r    g    b              s     t
		-20.0f, -0.9f, 20.0,		0.0f, 0.2f, 0.0f,	0.0f, 0.0f,	//	0
		20.0f, -0.9f, 20.0f,		0.5f, 0.5f, 0.0f,	0.0f, 1.0f,	//	1
		-20.0f, -0.9f, -20.0f,		0.5f, 0.5f, 0.0f,	1.0f, 0.0f,	//	2
		20.0f, -0.9f, -20.0f,		0.8f, 0.3f, 0.0f,	1.0f, 1.0f	//	3
	};
	
	unsigned int roofIndices[] = {
		0, 1, 2,
		1, 2, 3,
		3, 2, 4,
		0, 2, 4
	};
	
	GLfloat roofVertices[] = {
	//	   x    y    z  	  r    g     b		  s    t
		-0.8f, 0.8f, -0.8,	0.6f, 0.2f, 0.2f, 	0.0f, 1.0f,	// 0
		0.8f, 0.8f, -0.8f, 	0.6f, 0.2f, 0.2f,	1.0f, 1.0f,	// 1
		0.0f, 1.4f, 0.0f,	0.6f, 0.2f, 0.2f,	0.5f, 0.5f,	// 2
		0.8f, 0.8f, 0.8f, 	0.6f, 0.2f, 0.2f,	1.0f, 0.0f,	// 3
		-0.8, 0.8f, 0.8f,	0.6f, 0.2f, 0.2f,	0.0f, 0.0f	// 4	 
	};
	
	
	unsigned int doorIndices[] = {
		0, 1, 2,
		1, 2, 3
	};
	
	GLfloat doorVertices[] = {
	//	   x     y    z  		r    g    b  		  s    t
		-0.2f, -0.2f, -0.8f,		1.0f, 0.9f, 0.0f,	0.0f, 1.0f,	//	0
		-0.2f, -0.9f, -0.8f,		1.0f, 0.9f, 0.0f,	0.0f, 0.0f,	//	1
		0.2f, -0.2f, -0.8f,		1.0f, 0.9f, 0.0f,	1.0f, 1.0f,	//	2
		0.2f, -0.9f, -0.8f,		1.0f, 0.9f, 0.0f,	1.0f, 0.0f	//	3
	};
	
	unsigned int verticesSize = sizeof(vertices) / sizeof(vertices[0]);	
	unsigned int indicesSize = sizeof(indices) / sizeof(indices[0]);
	
	Mesh *house = new Mesh();
	house->createMesh(vertices, verticesSize, indices, indicesSize);	
	meshList.push_back(house);
	
	unsigned int floorVerticesSize = sizeof(floorVertices) / sizeof(floorVertices[0]);	
	unsigned int floorIndicesSize = sizeof(floorIndices) / sizeof(floorIndices[0]);
	
	Mesh *floor = new Mesh();
	floor->createMesh(floorVertices, floorVerticesSize, floorIndices, floorIndicesSize);	
	meshList.push_back(floor);
	
	unsigned int roofVerticesSize = sizeof(roofVertices) / sizeof(roofVertices[0]);	
	unsigned int roofIndicesSize = sizeof(roofIndices) / sizeof(roofIndices[0]);
	
	Mesh *roof = new Mesh();
	roof->createMesh(roofVertices, roofVerticesSize, roofIndices, roofIndicesSize);	
	meshList.push_back(roof);
	
	unsigned int doorVerticesSize = sizeof(doorVertices) / sizeof(doorVertices[0]);	
	unsigned int doorIndicesSize = sizeof(doorIndices) / sizeof(doorIndices[0]);
	
	Mesh *door = new Mesh();
	door->createMesh(doorVertices, doorVerticesSize, doorIndices, doorIndicesSize);	
	meshList.push_back(door);
}


int main()
{

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	GLWindow theWindow = GLWindow(1024,768, "Simon's House");
	theWindow.init();
   	theWindow.openWindow();
	//theWindow.openFullscreen();	
		
	createObject(); // this will make the mesh
	
	// load textures. I am using one texture for each object which I can do using OOP and putting the objects together to make one scene
	Texture brickTexture = Texture("bricks.png");
	brickTexture.loadTexture();
	Texture grassTexture = Texture("grass.png");
	grassTexture.loadTexture();
	Texture roofTexture = Texture("roof.png");
	roofTexture.loadTexture();
	Texture doorTexture = Texture("door.png");
	doorTexture.loadTexture();
	Shader shader = Shader();
	shader.compileShader(pVSFilename, pFSFilename);
	
	Camera camera = Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 1.0f);
	
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	
	mat4 projection = perspective(45.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, 100.0f);
	
	
	// loop until window closed
	while(!theWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		// get and handle user input events
		theWindow.pollEvents();
		
		camera.keyControl(theWindow.getKeys(), deltaTime);
		camera.mouseControl(theWindow.getXChange(), theWindow.getYChange());
		
		// clear window
		glClearColor(0.0f, 0.83f, 1.0f, 1.0f); // Blue sky!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.useShaderProgramme();
		uniformModel = shader.getModelLocation();
		uniformProjection = shader.getProjectionLocation();
		uniformView = shader.getViewLocation();
		
		
		mat4 model(1.0f); // new model variable we now need to declare with the added (1.0f)
		
		model = scale(model, vec3(2.9f, 3.0f, 2.9f)); // make bigger
		model = rotate(model,180 * toRadians, vec3(0.0f, 1.0f, 0.0f)); // spin round....note OpenGL is right handed!
		model = translate(model, vec3(0.0f, 0.4f, 4.0f)); // move back
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, value_ptr(model));
		
		// we activate each texture before each draw. Our house is made up of 3 objects the grass is a fouth object
		brickTexture.useTexture();  
		meshList[0]->drawMesh();
		grassTexture.useTexture();
		meshList[1]->drawMesh();
		roofTexture.useTexture();
		meshList[2]->drawMesh();
		doorTexture.useTexture();
		meshList[3]->drawMesh();
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));	
		
		shader.clearShaderProgramme();
		theWindow.swapBuffers();
	}
	
	return 0;
}
