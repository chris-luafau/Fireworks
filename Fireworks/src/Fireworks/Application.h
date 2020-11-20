#pragma once

#include "Core.h"

#include"Window.h"
#include "Fireworks/LayerStack.h"
#include "Fireworks/Events/Event.h"
#include "Fireworks/Events/ApplicationEvent.h"

#include "Fireworks/ImGui/ImGuiLayer.h"

// TEMPORARY
#include "Fireworks/Renderer/Shader.h"
#include "Fireworks/Renderer/Buffer.h"
#include "Fireworks/Renderer/VertexArray.h"

#include "Fireworks/Renderer/OrthographicCamera.h"

namespace Fireworks {

	class FIREWORKS_API Application {
	public:
		Application();
		virtual ~Application() = default;  // Must be virtual since it will be inherited by the Sandbox application.

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
