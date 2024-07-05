#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	static struct Vector3
	{
		virtual ~Vector3() = 0;

		static const glm::vec3 UP;
		static const glm::vec3 DOWN;
		static const glm::vec3 LEFT;
		static const glm::vec3 RIGHT;
		static const glm::vec3 FORWARD;
		static const glm::vec3 BACKWARD;
	};

	const glm::vec3 Vector3::UP = { 0.f, 1.f, 0.f };
	const glm::vec3 Vector3::DOWN = { 0.f, -1.f, 0.f };
	const glm::vec3 Vector3::LEFT = { -1.f, 0.f, 0.f };
	const glm::vec3 Vector3::RIGHT = { 1.f, 0.f, 0.f };
	const glm::vec3 Vector3::FORWARD = { 0.f, 0.f, 1.f };
	const glm::vec3 Vector3::BACKWARD = { 0.f, 0.f, -1.f };
}