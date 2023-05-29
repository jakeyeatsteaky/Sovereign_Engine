//#include <stdio.h>
//
//#include "GL/glew.h"
//
//#include "VertexArray.h"
//
//VertexArray::VertexArray() :
//	m_size(1)
//{
//	glGenVertexArrays(m_size, &m_idx);
//	glBindVertexArray(m_idx);
//}
//
//VertexArray::VertexArray(const VertexArray& other) :
//	m_idx(other.m_idx)
//{
//	glGenVertexArrays(m_size, &m_idx);
//	glBindVertexArray(m_idx);
//}
//
//unsigned int VertexArray::GetUniqueId()
//{
//	return m_idx;
//}
//
//void VertexArray::BindVertexArray() {
//	glBindVertexArray(m_idx);
//}
//
//void VertexArray::ClearFromBinding() {
//	glBindVertexArray(0);
//}
//
//void VertexArray::Destroy() {
//	printf("Deleting VAO object");
//	glDeleteVertexArrays((GLsizei)m_size, &m_idx);
//}
//
//void VertexArray::AddBuffer(IndexBuffer& buffer)
//{
//	m_buffers.push_back(buffer);
//}
//
//IndexBuffer& VertexArray::GetBuffer(size_t idx)
//{
//	return m_buffers[idx];
//}
//
//void VertexArray::BindBuffer(size_t idx)
//{
//	//m_buffers[idx].Bind()
//}