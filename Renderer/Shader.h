#pragma once
#include <glad/glad.h>
#include "../MainIncludes.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"

namespace Engine
{
	enum ShaderType
	{
		Programm,
		Fragment,
		Vert
	};

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void Use();
		void SetMatrix4F(const std::string uniformValueName, const glm::mat4& matrix) const;
	private:
		unsigned int m_ProgramID;
		std::shared_ptr<ShaderProgramSource> m_ShaderProgramSource;
	private:
		void InitializeShader(ShaderProgramSource& shaderProgramSource);
		std::string ReadShaderFile(const char* path);
		void CheckCompileError(unsigned int shader, Engine::ShaderType type);
	};
	
}


