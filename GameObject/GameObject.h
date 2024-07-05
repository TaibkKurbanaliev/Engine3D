#pragma once
#include "Model3D.h"
#include "Object.h"
#include "../Renderer/Texture.h"

namespace Engine
{
	class GameObject : public Object
	{
	public:
		GameObject();
		void Update();
		void TestUpdate(float direction);

		const std::shared_ptr<Model3D>& GetModel() const { return m_Model; };
		const std::shared_ptr<Texture>& GetTexture() const { return m_Texture; };

		void SetModel(const std::shared_ptr<Model3D>& model);
		void SetTexture(const std::shared_ptr<Texture>& texture);
		void SetPosition(const glm::vec3& position) override;
		void SetScale(const glm::vec3& scale) override;
		void SetRotation(const glm::vec3& rotation) override;
	private:
		std::shared_ptr<Model3D> m_Model;
		std::shared_ptr<Texture> m_Texture;
	};
}

