#pragma once
#include <glad/glad.h>
#include "../Core/Log.h"


namespace Engine
{
	class Texture
	{
	private:
		uint32_t m_RendererID;
		uint32_t m_Channels;
		uint32_t m_Width, m_Height;
		bool m_IsLoaded = false;
		GLenum m_InternalFormat, m_DataFormat;
	public:
		Texture(const char* path);
		~Texture();

		bool IsLoaded() const { return m_IsLoaded; }
		void Bind() const;
	};
}

