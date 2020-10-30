
#include <Fireworks.h>

class ExampleLayer : public Fireworks::Layer {
public:
	ExampleLayer() 
		: Layer("Example") {

	}

	void OnUpdate() override {
		FZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Fireworks::Event& event) override {
		FZ_TRACE("{0}", event);
	}
};

class Sandbox : public Fireworks::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushLayer(new Fireworks::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Fireworks::Application* Fireworks::CreateApplication() {
	return new Sandbox();
}