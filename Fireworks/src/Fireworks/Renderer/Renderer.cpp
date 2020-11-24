#include "fzpch.h"
#include "Renderer.h"

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
		shader->UploadUniformMat4("u_ProjectionView", s_SceneData->ProjectionViewMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}