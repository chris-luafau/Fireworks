#include <Fireworks.h>

#include "imgui/imgui.h"

class ExampleLayer : public Fireworks::Layer {
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {

		// To render a triangle, we need:
		// Vertex Array -> Holds references to the vertex and index buffers
		// Shader --> For now, we will use the shaders provided by the GPU.

		m_VertexArray.reset(Fireworks::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// Upload vertices to the GPU.
		std::shared_ptr<Fireworks::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Fireworks::VertexBuffer::Create(vertices, sizeof(vertices)));
		Fireworks::BufferLayout layout = {
			{ Fireworks::ShaderDataType::Float3, "a_Position" },
			{ Fireworks::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		// Abstract the creation of the index buffer by calling our custom API instead of directly calling OpenGL functions.
		std::shared_ptr<Fireworks::IndexBuffer> indexBuffer;
		indexBuffer.reset(Fireworks::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Fireworks::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		// Shader code: Vertex shader and Fragment shader.
		// Vertex shader handles the position of the vertices.
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ProjectionView;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);
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
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Fireworks::Shader(vertexSrc, fragmentSrc));

		// Draw a square
		std::shared_ptr<Fireworks::VertexBuffer> squareVB;
		squareVB.reset(Fireworks::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Fireworks::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Fireworks::IndexBuffer> squareIB;
		squareIB.reset(Fireworks::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ProjectionView;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.5, 1.0);
			}
		)";

		m_BlueShader.reset(new Fireworks::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override {
		if (Fireworks::Input::IsKeyPressed(FZ_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		else if (Fireworks::Input::IsKeyPressed(FZ_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed;

		if (Fireworks::Input::IsKeyPressed(FZ_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		else if (Fireworks::Input::IsKeyPressed(FZ_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Fireworks::Input::IsKeyPressed(FZ_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed;

		else if (Fireworks::Input::IsKeyPressed(FZ_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed;

		Fireworks::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fireworks::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Fireworks::Renderer::BeginScene(m_Camera);
		{
			Fireworks::Renderer::Submit(m_BlueShader, m_SquareVA);
			Fireworks::Renderer::Submit(m_Shader, m_VertexArray);
			Fireworks::Renderer::EndScene();
		}
	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(Fireworks::Event& event) override {

	}

private:
	std::shared_ptr<Fireworks::Shader> m_Shader;
	std::shared_ptr<Fireworks::VertexArray> m_VertexArray;
		
	std::shared_ptr<Fireworks::Shader> m_BlueShader;
	std::shared_ptr<Fireworks::VertexArray> m_SquareVA;

	Fireworks::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Fireworks::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Fireworks::Application* Fireworks::CreateApplication() {
	return new Sandbox();
}