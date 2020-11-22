#pragma once

#include "Fireworks/Core.h"
#include "Fireworks/Core/Timestep.h"
#include "Fireworks/Events/Event.h"

namespace Fireworks {

	class FIREWORKS_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};
}
