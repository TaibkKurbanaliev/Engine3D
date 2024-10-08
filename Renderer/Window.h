#pragma once
#include "glad/glad.h"
#include "SDL.h"
#include "glm/glm.hpp"
#include "../MainIncludes.h"
#include "SDL_image.h"
#include "Shader.h"
#include "glm/mat4x4.hpp"
#include "../GameObject/GameObject.h"
#include "Renderer.h"
#include "VertexArray.h"


namespace Engine
{
	class Window
	{
	public:
		Window();
		Window(std::string title, int width, int height);
		~Window();
		void Init();
		void DeInit(int error);
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		void WindowUpdate();
	private:
		unsigned int VBO_polygon, VAO_polygon, EBO_polygon;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;
		SDL_Window* m_Window = NULL;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<Shader> m_Shader;
		std::string m_Title = "OPENGL";
		int m_Width = 1920;
		int m_Height = 1080;

		GameObject gameObject1;
		GameObject gameObject2;
		Camera camera;

	};
}


