#include "Buffer.h"

namespace Engine
{
	VertexBuffer::VertexBuffer(float* data, size_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}


	IndexBuffer::IndexBuffer(uint32_t* data, size_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), data, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}