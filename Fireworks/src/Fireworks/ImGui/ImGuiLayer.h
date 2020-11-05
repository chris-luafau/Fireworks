#pragma once

#include "Fireworks/Layer.h"

#include "Fireworks/Events/KeyEvent.h"
#include "Fireworks/Events/MouseEvent.h"
#include "Fireworks/Events/ApplicationEvent.h"

namespace Fireworks {

	class FIREWORKS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}
