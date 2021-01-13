#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
}

void Mesh::createMesh(GLfloat *vertices, unsigned int numOfVertices, unsigned int *indices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;
		
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1); // colour
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2); // texture
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::drawMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
	glBindVertexArray(0);
}

Mesh::~Mesh()
{

}

