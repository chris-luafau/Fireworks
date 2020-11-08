#include "fzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>


namespace Fireworks {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		FZ_CORE_ASSERT(windowHandle, "Window handle is null.");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);

		// Initialize Glad. 
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FZ_CORE_ASSERT(status, "Failed to initialize Glad.");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}