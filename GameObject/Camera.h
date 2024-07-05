#pragma once
#include "../MainIncludes.h"
#include <glm/glm.hpp>
#include "Object.h"

namespace Engine
{
	class Camera : public Object
	{
	public:
		const char* UNIFORM_NAME = STRINGIFY(Camera);
	public:
		Camera();
		~Camera();

		const glm::vec3& GetTarget() const { return m_Target; };
		const glm::mat4& GetProjection() const { return *m_Projection; };

		void SetOrthographicProjection(float x, float y, float w, float h);
		void SetPerpectiveProjection(float width, float height);
		
	private:
		float m_FOV;
		float m_Distance;
		float m_Near;
		float m_Far;
		glm::vec3 m_Forward;
		std::unique_ptr<glm::mat4> m_Projection;
		glm::vec3 m_Target = {0.f,0.f,0.f};
	};

}

