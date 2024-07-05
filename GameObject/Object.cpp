#include "Object.h"

namespace Engine
{
	Object::Object()
	{
		Position = glm::vec3(0.f);
		Scale = glm::vec3(1.f);
		Rotation = glm::vec3(0.f);
		m_ObjectMatrix = std::make_unique<glm::mat4>(1.f);
	}

	void Object::SetPosition(const glm::vec3& pos)
	{
		Position = pos;
		m_ObjectMatrix = std::make_unique<glm::mat4>(glm::translate(*m_ObjectMatrix, Position));
	}

	void Object::SetScale(const glm::vec3& scale)
	{
		Scale.x = std::abs(scale.x);
		Scale.y = std::abs(scale.y);
		Scale.z = std::abs(scale.z);

		m_ObjectMatrix = std::make_unique<glm::mat4>(glm::scale(*m_ObjectMatrix, Scale));
	}

	void Object::SetRotation(const glm::vec3& rotation)
	{
		Rotation = rotation;

		m_ObjectMatrix = std::make_unique<glm::mat4>(glm::rotate(*m_ObjectMatrix, glm::radians(Rotation.x), glm::vec3(1.f, 0.f, 0.f)));
		m_ObjectMatrix = std::make_unique<glm::mat4>(glm::rotate(*m_ObjectMatrix, glm::radians(Rotation.y), glm::vec3(0.f, 1.f, 0.f)));
		m_ObjectMatrix = std::make_unique<glm::mat4>(glm::rotate(*m_ObjectMatrix, glm::radians(Rotation.z), glm::vec3(0.f, 0.f, 1.f)));
	}

	void Object::SetObjectMatrix(const glm::mat4& matrix)
	{
		m_ObjectMatrix = std::make_unique<glm::mat4>(matrix);
	}
}