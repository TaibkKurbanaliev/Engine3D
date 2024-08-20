#include "Mesh.h"


namespace Engine
{

	Mesh::Mesh(const VertexBuffer& VBO, const IndexBuffer& EBO, const VertexArray& VAO)
	{
		m_VBO = std::make_shared<VertexBuffer>(VBO);
		m_EBO = std::make_shared<IndexBuffer>(EBO);
		m_VAO = std::make_shared<VertexArray>(VAO);

		BufferLayout* layout = new BufferLayout{
			{ ShaderDataType::Float3, "aPos"},
			{ ShaderDataType::Float4, "inColors"},
			{ ShaderDataType::Float3, "inNormals"},
			{ ShaderDataType::Float2, "inTextureCoords"}
		};

		m_VBO->SetLayout(*layout);
	}
}