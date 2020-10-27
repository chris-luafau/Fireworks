#include "fzpch.h"
#include "Application.h"

#include "Fireworks/Events/ApplicationEvent.h"
#include "Fireworks/Log.h"

namespace Fireworks {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}
