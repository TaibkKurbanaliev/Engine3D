#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

namespace Engine
{
	Texture::Texture(const char* path)
	{
		int width, height, channels;
		unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
		
		if (!data)
		{
			ENGINE_CORE_WARN("Failed to load Image");
			return;
		}
			
		m_IsLoaded = true;

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		if (internalFormat & dataFormat)
		{
			ENGINE_CORE_WARN("Format not supported!");
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

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