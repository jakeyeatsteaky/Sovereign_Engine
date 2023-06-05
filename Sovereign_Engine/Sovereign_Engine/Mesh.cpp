#include "Mesh.h"


void Mesh::Bind() {
	m_vao.Bind();
}

void Mesh::SetShader()
{
	std::shared_ptr<Shader> shadProg = m_shaderProgram.lock();
	if(shadProg)
		shadProg->UseProgram();
}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
