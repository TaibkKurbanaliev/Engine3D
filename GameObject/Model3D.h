#pragma once
#include "../Renderer/Shader.h"
#include "glm/mat4x4.hpp"

namespace Engine
{
	class Model3D
	{
	public:
		const char* UNIFORM_NAME = STRINGIFY(Model3D);
	public:
		Model3D(const char* vertexPath, const char* fragmentPath);
		void SetMatrix(std::string uniformName, const glm::mat4& matrix) const;
		const std::unique_ptr<Shader>& GetShader() const { return m_Shader; };
	private:
		std::unique_ptr<Shader> m_Shader;

	};
}

