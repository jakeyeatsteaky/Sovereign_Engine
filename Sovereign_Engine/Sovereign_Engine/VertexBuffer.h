#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer(size_t n);
	VertexBuffer(const VertexBuffer& other);
	VertexBuffer() = default;
	~VertexBuffer() = default;

	void Bind(float* vertices, GLsizeiptr sizevert);
	unsigned int GetIdx();
	void ClearFromBinding();
	void Destroy();

private:
	unsigned int vbo_idx;
	size_t size;
};

#endif