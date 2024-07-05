#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

namespace Engine
{
	Texture::Texture(const char* path)
	{
		unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_Channels, 0);
		
		if (!data)
			ENGINE_CORE_WARN("Failed to load Image");

		ENGINE_CORE_INFO(std::to_string(m_Channels));

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind() const
	{
		glBindTextureUnit(0, m_RendererID);
	}
}