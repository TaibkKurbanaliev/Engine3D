#include "GameObject.h"
#include <SDL.h>


namespace Engine
{

	GameObject::GameObject()
	{
	}

	void GameObject::Update()
	{
		//�������������
		//m_Model->SetMatrix("model");
	}

	/*void GameObject::TestUpdate(float direction)
	{
		m_Rotation.z =  direction * 0.01;

		if (m_Rotation.z > 360 || m_Rotation.z < -360)
			m_Rotation.z = 0;

		m_Model->SetMatrix("model", *m_ModelMatrix,nullptr,&m_Rotation,nullptr);
	}*/

	void GameObject::SetTexture(const std::shared_ptr<Texture>& texture)
	{
		m_Texture = texture;
	}
	void GameObject::SetPosition(const glm::vec3 &position)
	{
		this->Object::SetPosition(position);
	}
	void GameObject::SetScale(const glm::vec3& scale)
	{
		this->Object::SetScale(scale);
	}
	void GameObject::SetRotation(const glm::vec3& rotation)
	{
		this->Object::SetRotation(rotation);
	}
}