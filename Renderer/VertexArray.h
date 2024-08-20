#pragma once
#include "../MainIncludes.h"
#include "Buffer.h"

namespace Engine
{

	class VertexArray
	{
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	public:
		VertexArray();
		~VertexArray();

		uint32_t GetRendererID() const { return m_RendererID; }

		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		const std::shared_ptr<VertexBuffer>& GetVertexBuffer(size_t index) const { if (index < m_VertexBuffers.size()) return m_VertexBuffers[index]; }
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
	};
}