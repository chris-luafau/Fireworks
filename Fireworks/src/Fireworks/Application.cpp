#include "fzpch.h"
#include "Application.h"

#include "Fireworks/Log.h"
#include "Input.h"

#include <glad/glad.h>

namespace Fireworks {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		FZ_CORE_ASSERT(s_Insatance, "Application already exists.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// To render a triangle, we need:
		// Vertex Array
		// Vertex Buffer
		// Index buffer
		// Shader --> For now, we will use the shaders provided by the GPU.

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		// Upload vertices to the GPU.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Tell OpenGL the layout/format of the data.
		// I.e. OpenGL doesn't know that the vertices data is a 3x3 matrix.
		// It just sees them as bytes of data.
		glEnableVertexAttribArray(0);
		// Start at index 0, there are 3 items, they're floats, won't be normalized, reserve space, and there is no offset between
		// multiple attributes (we only have 1 attribute in this case - vertices).
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		// OpenGL refers to index buffers as element buffers.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Shader code: Vertex shader and Fragment shader.
		// Vertex shader handles the position of the vertices.
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;	
		
			out vec3 v_Position;			

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		// Fragment shader handles the color of the vertices.
		// We will base the colors off the position of the vertices to create a gradient effect.
		// Since the clipspace of the window is from -1 to 1 and rgb ranges from 0 to 1,
		// the colors don't come out great.
		// To fix, we will half the vertex position and add 0.5 to move the value into the 0 to 1 range.
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;			

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Bind the vertex array and draw.
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->Begin(); 
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
