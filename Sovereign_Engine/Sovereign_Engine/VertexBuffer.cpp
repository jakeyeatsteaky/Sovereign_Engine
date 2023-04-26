#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(size_t n) : 
	size(n) 
{
	glGenBuffers((GLsizei)size, &vbo_idx);
}

VertexBuffer::VertexBuffer(const VertexBuffer& other) : 
	size(other.size), 
	vbo_idx(other.vbo_idx) 
{

}

void VertexBuffer::Bind(float* vertices, GLsizeiptr sizevert) 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ARRAY_BUFFER, sizevert, vertices, GL_STATIC_DRAW);
}

unsigned int VertexBuffer::GetIdx() 
{
	return vbo_idx;
}


void VertexBuffer::ClearFromBinding()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Destroy() 
{
	glDeleteBuffers(size, &vbo_idx);
}