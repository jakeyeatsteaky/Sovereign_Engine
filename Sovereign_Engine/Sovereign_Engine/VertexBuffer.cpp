//#include "VertexBuffer.h"
//
//VertexBuffer::VertexBuffer()
//{
//	glGenBuffers(1, &vbo_idx);
//	glGenBuffers(1, &ebo_idx);
//}
//
//VertexBuffer::VertexBuffer(const VertexBuffer& other) :
//	vbo_idx(other.vbo_idx),
//	ebo_idx(other.ebo_idx)
//{
//
//}
//
//void VertexBuffer::Bind(float vertices[], unsigned int indices[], GLsizeiptr sizevert, GLsizeiptr sizeInd)
//{
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_idx);
//	glBufferData(GL_ARRAY_BUFFER, sizevert, vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_idx);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInd, indices, GL_STATIC_DRAW);
//}
//
//unsigned int VertexBuffer::GetIdx() 
//{
//	return vbo_idx;
//}
//
//
//void VertexBuffer::ClearFromBinding()
//{
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void VertexBuffer::Destroy() 
//{
//	glDeleteBuffers(1, &vbo_idx);
//	glDeleteBuffers(1, &ebo_idx);
//}