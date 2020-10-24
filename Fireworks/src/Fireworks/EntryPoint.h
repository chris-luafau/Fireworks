#pragma once

#ifdef FZ_PLATFORM_WINDOWS

extern Fireworks::Application* Fireworks::CreateApplication();

int main(int argc, char** argv) {

	Fireworks::Log::Init();
	FZ_CORE_WARN("Initialized Log.");
	FZ_INFO("Welcome.");

	auto app = Fireworks::CreateApplication();
	app->Run();
	delete app;
}

#endif
