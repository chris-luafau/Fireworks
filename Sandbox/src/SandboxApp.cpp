#include <Fireworks.h>

class ExampleLayer : public Fireworks::Layer {
public:
	ExampleLayer() 
		: Layer("Example") {

	}

	void OnUpdate() override {
		// Test FZ Keycodes.
		if (Fireworks::Input::IsKeyPressed(FZ_KEY_TAB))
			FZ_TRACE("Tab key pressed (polled).");
	}

	void OnEvent(Fireworks::Event& event) override {
		// Temporary: Checking keycodes.
		if (event.GetEventType() == Fireworks::EventType::KeyPressed) {
			Fireworks::KeyPressedEvent& e = (Fireworks::KeyPressedEvent&)event;
			if (e.GetKeyCode() == FZ_KEY_TAB)
				FZ_TRACE("Tab key pressed (event/pushed).");
			FZ_TRACE("{0}",(char)e.GetKeyCode());
		}
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