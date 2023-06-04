#ifndef MESH_H
#define MESH_H
#include "GL/glew.h"
#include "VertexArray.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	void LoadMesh(const float vertices[], const float indices[], const GLuint vertexCount, const GLuint indexCount);
	void Draw();
	void SetShader();

private:
	VertexArray m_vao;
	
};


#endif