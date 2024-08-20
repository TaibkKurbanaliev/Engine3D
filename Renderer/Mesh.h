#pragma once
#include "Buffer.h"
#include "VertexArray.h"
#include "../MainIncludes.h"

namespace Engine
{
	class Mesh
	{
	public:
		Mesh(const VertexBuffer& VBO, const IndexBuffer& EBO, const VertexArray& VAO);

		const VertexArray& GetVAO() const { return *m_VAO; }
		const IndexBuffer& GetEBO() const { return *m_EBO; }
		const VertexBuffer& GetVBO() const { return *m_VBO; }

	private:
		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_EBO;
		std::shared_ptr<VertexArray> m_VAO;
	};
}

