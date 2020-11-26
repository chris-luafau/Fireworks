#include "fzpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Fireworks {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene() {
		// TODO
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
							const std::shared_ptr<VertexArray>& vertexArray, 
							const glm::mat4& transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ProjectionView", s_SceneData->ProjectionViewMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		// TODO
		// mi.Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}