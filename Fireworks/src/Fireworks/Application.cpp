
#include "Application.h"

#include "Events/Event.h"
#include "Fireworks/Events/ApplicationEvent.h"
#include "Fireworks/Log.h"

namespace Fireworks {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		// Testing
		WindowResizeEvent e(1280, 720);
		FZ_TRACE(e);

		while (true);
	}

}
