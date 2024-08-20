#pragma once
#include "../MainIncludes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	// The parent class for all objects in the scene containing basic attributes and methods
	class Object
	{
	protected:
		glm::vec3 Position;
		glm::vec3 Scale;
		glm::vec3 Rotation;
	private:
		std::unique_ptr<glm::mat4> m_ObjectMatrix;
	public:
		Object();
		virtual ~Object() {};

#pragma region Getters and Setters
		const glm::vec3& GetPosition() const { return Position; };
		const glm::vec3& GetScale() const { return Scale; };
		const glm::vec3& GetRotation() const { return Rotation; };
		const glm::mat4& GetObjectMatrix() const { return *m_ObjectMatrix; };

		virtual void SetPosition(const glm::vec3& pos);
		virtual void SetScale(const glm::vec3& scale);
		virtual void SetRotation(const glm::vec3& rotation);
		virtual void SetObjectMatrix(const glm::mat4& matrix);
#pragma endregion

	};
}
