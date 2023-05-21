#ifndef MESH_H
#define MESH_H
#include "SDL_opengl.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	void LoadMesh(const float vertices[], const float indices[], const GLuint vertexCount, const GLuint indexCount);
	void Draw();
	void SetShader();

private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_vertexCount;
	GLuint m_indexCount;
};


#endif