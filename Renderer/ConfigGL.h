#pragma once
#include "SDL.h"
#include "glad/glad.h"
#include "Buffer.h"
#include "iostream"

namespace GLInit
{
	GLenum ShaderDataToGLType(Engine::ShaderDataType type)
	{
		switch (type)
		{
		case Engine::ShaderDataType::Float:    return GL_FLOAT;
		case Engine::ShaderDataType::Float2:   return GL_FLOAT;
		case Engine::ShaderDataType::Float3:   return GL_FLOAT;
		case Engine::ShaderDataType::Float4:   return GL_FLOAT;
		case Engine::ShaderDataType::Mat3:     return GL_FLOAT;
		case Engine::ShaderDataType::Mat4:     return GL_FLOAT;
		case Engine::ShaderDataType::Int:      return GL_INT;
		case Engine::ShaderDataType::Int2:     return GL_INT;
		case Engine::ShaderDataType::Int3:     return GL_INT;
		case Engine::ShaderDataType::Int4:     return GL_INT;
		case Engine::ShaderDataType::Bool:     return GL_BOOL;
		}
	}

	void OnResize(SDL_Window* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void InitializeBuffers(unsigned int &VBO, unsigned int& VAO, unsigned int& EBO, const float* vertices, const unsigned int* indices)
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 8, vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void InitializeBuffers(Engine::VertexBuffer& vertexBuffer, Engine::IndexBuffer& indexBuffer )
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		uint32_t index = 0;

		for (const auto& element : vertexBuffer.GetLayout())
		{
			std::cout << std::format("{} {} {} {} {} ", index, element.GetComponentCount(), std::to_string(ShaderDataToGLType(element.Type)),
				vertexBuffer.GetLayout().GetStride() * sizeof(ShaderDataToGLType(element.Type)), element.Offset);
			
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataToGLType(element.Type),
				GL_FALSE,
				vertexBuffer.GetLayout().GetStride() * sizeof(ShaderDataToGLType(element.Type)),
				(const void*)element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}
	}
}