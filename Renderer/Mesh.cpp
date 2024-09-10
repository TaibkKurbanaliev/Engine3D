#include "Mesh.h"


namespace Engine
{

	Mesh::Mesh(const std::shared_ptr<VertexBuffer>& VBO, const std::shared_ptr<IndexBuffer>& EBO, const std::shared_ptr<VertexArray>& VAO)
	{
		m_VBO = VBO;
		m_EBO = EBO;
		m_VAO = VAO;

		BufferLayout* layout = new BufferLayout{
			{ ShaderDataType::Float3, "aPos"},
			{ ShaderDataType::Float4, "inColors"},
			{ ShaderDataType::Float3, "inNormals"},
			{ ShaderDataType::Float2, "inTextureCoords"}
		};

		m_VBO->SetLayout(*layout);
	}
}