#pragma once

#ifdef FZ_PLATFORM_WINDOWS

extern Fireworks::Application* Fireworks::CreateApplication();

int main(int argc, char** argv) {
	auto app = Fireworks::CreateApplication();
	app->Run();
	delete app;
}

#endif
