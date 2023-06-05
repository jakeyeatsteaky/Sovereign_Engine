#include "GL/glew.h"
#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vaoIdx);
	glBindVertexArray(m_vaoIdx);
}

VertexArray::VertexArray(const VertexArray& other) : m_vaoIdx(other.m_vaoIdx)
{
	glGenVertexArrays(1, &m_vaoIdx);
	glBindVertexArray(m_vaoIdx);
}
 
VertexArray::~VertexArray()
{
	Destroy();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_vaoIdx);
}

unsigned int VertexArray::GetIdx()
{
	return m_vaoIdx;
}

void VertexArray::Destroy()
{
	// 
}

void VertexArray::ClearFromBinding()
{
	glBindVertexArray(0);
}
