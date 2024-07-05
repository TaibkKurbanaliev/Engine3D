#include "Model3D.h"

namespace Engine
{
	Model3D::Model3D(const char* vertexPath, const char* fragmentPath)
	{
		m_Shader = std::make_unique<Shader>(vertexPath, fragmentPath);
		m_Shader->Use();
	}

	void Model3D::SetMatrix(std::string uniformName, const glm::mat4& matrix) const
	{
		m_Shader->SetMatrix4F(uniformName, matrix);
		m_Shader->Use();
	}

}