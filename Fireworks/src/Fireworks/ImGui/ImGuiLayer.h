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
		/***
		virtual void OnUpdate() override;
		*/
		void Begin();
		void End();
		/***
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		*/
	private:
		float m_Time = 0.0f;
	};

}
