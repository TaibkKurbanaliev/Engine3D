#pragma once
#include <glad/glad.h>
#include "../Core/Log.h"


namespace Engine
{
	class Texture
	{
	private:
		unsigned int m_RendererID;
		int m_Width;
		int	m_Height;
		int	m_Channels;
	public:
		Texture(const char* path);
		~Texture();

		void Bind() const;
	};
}

