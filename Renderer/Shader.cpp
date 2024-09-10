#include "Shader.h"
#include <fstream>


namespace Engine 
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		m_ShaderProgramSource = std::make_shared<ShaderProgramSource>();
		m_ShaderProgramSource->VertexSource = ReadShaderFile(vertexPath);
		m_ShaderProgramSource->FragmentSource = ReadShaderFile(fragmentPath);

		InitializeShader(*m_ShaderProgramSource);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	void Shader::Use()
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::SetMatrix4F(const std::string uniformValueName, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, uniformValueName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::InitializeShader(ShaderProgramSource& shaderProgramSource)
	{
		const char* vertex = m_ShaderProgramSource->VertexSource.c_str();
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertex, NULL);
		glCompileShader(vertexShader);

		// Компиляция и настройка фрагментного шейдера
		const char* fragment = m_ShaderProgramSource->FragmentSource.c_str();
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragment, NULL);
		glCompileShader(fragmentShader);

		// Создание шейдерной программы и привязка шейдеров
		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, vertexShader);
		glAttachShader(m_ProgramID, fragmentShader);
		glLinkProgram(m_ProgramID);
		glUseProgram(m_ProgramID);
		CheckCompileError(m_ProgramID, Programm);
	}

	std::string Shader::ReadShaderFile(const char* path)
	{
		std::string source;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			shaderFile.open(path);
			std::string line = "";

			if (!shaderFile.is_open())
			{
				ENGINE_CORE_FATAL(std::format("Failed to open file {}", path));
			}
			else
			{
				while (!shaderFile.eof())
				{
					std::getline(shaderFile, line);
					source.append(line + "\n");
				}

				shaderFile.close();
			}
		}
		catch (std::ifstream::failure& e)
		{
			ENGINE_CORE_FATAL(std::format("Failed to read file"));
		}

		return source.c_str();
	}

	void Shader::CheckCompileError(unsigned int shader, ShaderType type)
	{
		int success;
		char infoLog[1024];

		if (type == ShaderType::Programm)
		{
			glGetProgramiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				ENGINE_CORE_FATAL(std::format("ERROR::PROGRAM_LINKING_ERROR of type: "));
			}
		}
		else
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				ENGINE_CORE_FATAL(std::format("ERROR::SHADER_COMPILATION_ERROR of type:"));
			}
		}
	}
}

