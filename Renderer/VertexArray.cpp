#include "VertexArray.h"

namespace Engine
{
	inline GLenum ShaderDataToGLType(Engine::ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}
	}

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		int index = 0;

		for (const auto& element : vertexBuffer->GetLayout())
		{
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataToGLType(element.Type),
				element.Normalized,
				vertexBuffer->GetLayout().GetStride() * sizeof(ShaderDataToGLType(element.Type)),
				(const void*)element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}

		glBindVertexArray(m_RendererID);
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);

		m_IndexBuffer = indexBuffer;
	}
}
