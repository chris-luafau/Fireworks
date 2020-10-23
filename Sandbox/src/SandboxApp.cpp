
#include <Fireworks.h>

class Sandbox : public Fireworks::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Fireworks::Application* Fireworks::CreateApplication() {
	return new Sandbox();
}