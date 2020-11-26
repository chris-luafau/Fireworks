#include "fzpch.h"
#include "Shader.h"

#include "glad/glad.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

//#include <glm/gtc/type_ptr.hpp> // value_ptr()

namespace Fireworks {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    FZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		FZ_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}