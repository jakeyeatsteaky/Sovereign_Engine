//#ifndef VERTEX_ARRAY_H
//#define VERTEX_ARRAY_H
//
//#include <vector>
//
//#include "IndexBuffer.h"
//
//
//class VertexArray
//{
//public:
//	VertexArray();
//	VertexArray(const VertexArray& other);
//	~VertexArray() = default;
//
//	unsigned int GetUniqueId();
//	void BindVertexArray();
//	void BindBuffer(size_t idx);
//	void ClearFromBinding();
//	void Destroy();
//	void AddBuffer(IndexBuffer& buffer);
//	IndexBuffer& GetBuffer(size_t idx);
//
//private:
//	size_t m_size;
//	std::vector<IndexBuffer> m_buffers;
//	unsigned int m_idx;
//};
//
//
//#endif