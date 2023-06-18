#include "Mesh.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"

Mesh::Mesh(std::weak_ptr<Shader> shaderProgram, std::weak_ptr<Texture> meshTexture) :
	m_shaderProgram(shaderProgram),
	m_meshTexture(meshTexture)
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] = { 
		0, 1, 3,  
		1, 2, 3   
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	};

	float texCoords[] = {
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	VertexLayout attributeLayout_3(3);

	m_vao.Bind();
	VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	IndexBuffer indexBuffer(indices, sizeof(indices));
	attributeLayout_3.SetLayout(0, 3, 0, 0);	// Set Layout: Position idx 0
	
	VertexBuffer colorBuffer(colors, sizeof(colors));
	attributeLayout_3.SetLayout(1, 3, 0, 0);	// Set Layout: Color idx 1

	VertexBuffer texCoordBuffer(texCoords, sizeof(texCoords));
	attributeLayout_3.SetLayout(2, 2, 0, 0);	// Set Layout: TexCoords idx 2

	// Clear bindings (don't clear index buffer)
	texCoordBuffer.ClearFromBinding();
	colorBuffer.ClearFromBinding();
	vertexBuffer.ClearFromBinding();
	m_vao.ClearFromBinding();
}

void Mesh::Bind() {
	m_vao.Bind();
}

void Mesh::SetShader()
{
	std::shared_ptr<Shader> shadProg = m_shaderProgram.lock();
	if(shadProg)
		shadProg->UseProgram();
}

void Mesh::SetTexture()
{
	std::shared_ptr<Texture> texture = m_meshTexture.lock();
	if (texture)
		texture->Bind();
}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::Render()
{
	SetTexture();
	SetShader();
	Bind();
	Draw();
}
