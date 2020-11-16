#pragma once

#include "RenderCommand.h"

namespace Fireworks {

	class Renderer {
	public:
		// TODO
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}