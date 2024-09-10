#include "Renderer.h"


namespace Engine
{
	Renderer::Renderer(const Shader& shader)
	{
		m_Shader = std::make_shared<Shader>(shader);
	}

	//�������������
	void Renderer::Draw(const Camera& cameraMatrix, const GameObject& gameObject, const std::shared_ptr<VertexArray> vertexArray) const
	{
		/*gameObject.GetModel()->GetShader()->SetMatrix4F(gameObject.GetModel()->UNIFORM_NAME, cameraMatrix.GetProjection()
			* cameraMatrix.GetObjectMatrix()
			* gameObject.GetObjectMatrix());*/

		m_Shader->SetMatrix4F("Model3D", cameraMatrix.GetProjection()
			* cameraMatrix.GetObjectMatrix()
			* gameObject.GetObjectMatrix());
		m_Shader->Use();

		if (gameObject.GetTexture().get())
			gameObject.GetTexture()->Bind();

		glBindVertexArray(vertexArray->GetRendererID());
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

}