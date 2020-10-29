#pragma once

#include "Core.h"

#include"Window.h"
#include "Fireworks/LayerStack.h"
#include "Fireworks/Events/Event.h"
#include "Fireworks/Events/ApplicationEvent.h"



namespace Fireworks {

	class FIREWORKS_API Application {
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
		virtual ~Application();  // Must be virtual since it will be inherited by the Sandbox application.

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

