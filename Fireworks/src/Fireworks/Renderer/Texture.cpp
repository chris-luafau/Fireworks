#include "fzpch.h"
#include "Texture.h"

#include "Renderer.h"

namespace Fireworks {

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		// TODO
		// switch (Renderer::GetAPI()) {
		// 
		// }

		FZ_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}