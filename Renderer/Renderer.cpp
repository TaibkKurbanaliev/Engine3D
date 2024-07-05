#include "Renderer.h"

namespace Engine
{
	//Отрефакторить
	void Renderer::Draw(const Camera& cameraMatrix, const GameObject& gameObject) const
	{
		gameObject.GetModel()->GetShader()->SetMatrix4F(gameObject.GetModel()->UNIFORM_NAME, cameraMatrix.GetProjection()  
																						   * cameraMatrix.GetObjectMatrix() 
																						   * gameObject.GetObjectMatrix());
		
		if (gameObject.GetTexture().get())
			gameObject.GetTexture()->Bind();
	}
}