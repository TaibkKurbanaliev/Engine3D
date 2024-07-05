#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/Camera.h"

namespace Engine
{
	class Renderer
	{
	public:
		void Draw(const Camera& camera, const GameObject& gameObject) const;
	};
}

