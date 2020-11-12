#include "fzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>


namespace Fireworks {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle) {
		FZ_CORE_ASSERT(windowHandle, "Window handle is null.");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);

		// Initialize Glad. 
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FZ_CORE_ASSERT(status, "Failed to initialize Glad.");

		FZ_CORE_INFO("OpenGL Info:");
		FZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}