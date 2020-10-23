#pragma once

#include "Core.h"

namespace Fireworks {

	class FIREWORKS_API Application {
	public:
		Application();
		virtual ~Application();  // Must be virtual since it will be inherited by the Sandbox application.

		void Run();
	};


	// To be defined in CLIENT
	Application* CreateApplication();

}

