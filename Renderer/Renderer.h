#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/Camera.h"
#include "VertexArray.h"

namespace Engine
{
	class Renderer
	{
	public:
		void Draw(const Camera& cameraMatrix, const GameObject& gameObject, const std::shared_ptr<VertexArray> vertexArray) const;
	};
}

