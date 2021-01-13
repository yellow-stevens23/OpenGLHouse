#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <iostream>

using namespace std;


class Mesh
{
    public:
        Mesh();
        void createMesh(GLfloat *vertices, unsigned int numOfVertices, unsigned int *indices, unsigned int numOfIndices);
        void drawMesh();
        virtual ~Mesh();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;
};

#endif // MESH_H

