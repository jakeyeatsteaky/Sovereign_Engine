#ifndef MESH_H
#define MESH_H
#include "GL/glew.h"
#include "VertexArray.h"
#include "Shaders.h"

class Mesh
{
public:
	// Apply the rule of five here - potentiall pass a Vertex Array by const reference, rvalue reference, etc
	Mesh(VertexArray&& vao, std::weak_ptr<Shader> shaderProgram) : m_vao(std::move(vao)), m_shaderProgram(shaderProgram) {}
	~Mesh() = default;
	
	void Bind();
	void Draw();
	void SetShader();

private:
	VertexArray m_vao;
	std::weak_ptr<Shader> m_shaderProgram;
};


#endif