#include "fzpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fireworks {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}