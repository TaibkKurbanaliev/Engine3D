#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/Camera.h"
#include "VertexArray.h"

#include "Shader.h"

namespace Engine
{
	class Renderer
	{
	public:
		Renderer(const Shader& shader);
		void Draw(const Camera& cameraMatrix, const GameObject& gameObject, const std::shared_ptr<VertexArray> vertexArray) const;

	private:
		std::shared_ptr<Shader> m_Shader;
	};
}

