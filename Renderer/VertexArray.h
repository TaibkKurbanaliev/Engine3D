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

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
	};
}