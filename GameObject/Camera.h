#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "../MainIncludes.h"
#include <glm/glm.hpp>
#include "Object.h"
#include <glm/gtx/quaternion.hpp>
#include "../Preprocessor.h"

namespace Engine
{
	class Camera : public Object
	{
	public:
		const char* UNIFORM_NAME = STRINGIFY(Camera);
	private:
		float m_MovementSpeed = 2.f;
		float m_FOV;
		float m_Distance;
		float m_Near;
		float m_Far;
		float m_MouseSensitivity = 5.f;

		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		std::unique_ptr<glm::mat4> m_Projection;
		glm::vec3 m_Target = { 0.f,0.f,0.f };
	
	public:
		Camera();
		~Camera();

		void SetPosition(const glm::vec3& position) override;
		void SetRotation(const glm::vec3& rotation) override { Rotate(rotation.x, rotation.y); };
		void Rotate(float xOffset, float yOffset);

		const glm::vec3& GetTarget() const { return m_Target; };
		const glm::mat4& GetProjection() const { return *m_Projection; };

		void SetOrthographicProjection(float x, float y, float w, float h);
		void SetPerpectiveProjection(float width, float height);
		

		void OnUpdate();
		
	private:
		void UpdateVectors();
	};
}

