#include "Camera.h"

namespace Engine
{
	Camera::Camera()
	{
		SetPosition({ 0.f, 0.f, 0.4f });
		SetObjectMatrix(glm::lookAt(Position, m_Target, glm::vec3(0.f, 1.f, 0.f)));
		SetPerpectiveProjection(1600, 900);
		m_Near = 0.01f;
		m_Far = 100.f;
		m_FOV = 45.f;
		/*glm::vec3 rotation = { 0.f, 15.f, 0.f };
		SetRotation(rotation);*/
	}
	Camera::~Camera()
	{
	}
	void Camera::SetOrthographicProjection(float left, float right, float bottom, float top)
	{
		// сделать проверку корректности данных
		m_Projection = std::make_unique<glm::mat4>(glm::ortho(left, right, bottom, top, m_Near, m_Far));
	}
	void Camera::SetPerpectiveProjection(float width, float height)
	{
		m_Projection = std::make_unique<glm::mat4>(glm::perspective(m_FOV, width / height, m_Near, m_Far));
	}
}