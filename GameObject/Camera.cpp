#include "Camera.h"
#include "../Core/Time.h"

namespace Engine
{
	Camera::Camera()
	{
		SetPosition({ 0.f, 0.f, 5.4f });
		m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		Rotation.x = 90.f;
		Rotation.y = 0.f;
		m_Near = 0.01f;
		m_Far = 1000.f;
		m_FOV = 45.f;
		SetPerpectiveProjection(1600, 900);
		Rotate(0, 0);
	}

	Camera::~Camera()
	{

	}

	void Camera::SetPosition(const glm::vec3& direction)
	{
		float velocity = m_MovementSpeed * Time::GetDeltaTime();
		if (direction.z > 0)
			Position -= m_Front * velocity;
		if (direction.z < 0)
			Position += m_Front * velocity;
		if (direction.x > 0)
			Position += m_Right * velocity;
		if (direction.x < 0)
			Position -= m_Right * velocity;
	}

	void Camera::OnUpdate()
	{
		SetObjectMatrix(glm::lookAt(Position, Position + m_Front, m_Up));
	}

	void Camera::UpdateVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.y));
		front.y = sin(glm::radians(Rotation.y));
		front.z = sin(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.y));
		m_Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	}
	
	void Camera::Rotate(float xOffset, float yOffset)
	{
		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		Rotation.x += xOffset;
		Rotation.y -= yOffset;


		if (Rotation.y > 89.0f)
			Rotation.y = 89.0f;
		if (Rotation.y < -89.0f)
			Rotation.y = -89.0f;


		// update Front, Right and Up Vectors using the updated Euler angles
		UpdateVectors();
	}


	void Camera::SetOrthographicProjection(float left, float right, float bottom, float top)
	{
		// сделать проверку корректности данных
		m_Projection = std::make_unique<glm::mat4>(glm::ortho(left, right, bottom, top, m_Near, m_Far));
	}

	void Camera::SetPerpectiveProjection(float width, float height)
	{
		m_Projection = std::make_unique<glm::mat4>(glm::perspective(glm::radians(m_FOV), width / height, m_Near, m_Far));
	}
}