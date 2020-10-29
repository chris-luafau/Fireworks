#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Fireworks/Events/ApplicationEvent.h"

#include"Window.h"

namespace Fireworks {

	class FIREWORKS_API Application {
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
		virtual ~Application();  // Must be virtual since it will be inherited by the Sandbox application.
		
		void OnEvent(Event& e);
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

