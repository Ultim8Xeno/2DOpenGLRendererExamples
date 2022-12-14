#include "Window.h"
#include "Debug.h"
#include "Input.h"
#include <iostream>
#include "Renderer.h"

namespace OpenGLRenderer {

	Window::Window(const std::string& name, const Vec2& dim, uint8_t windowHints)
		: dimensions(dim)
	{
		ASSERT(glfwInit());

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, windowHints & WINDOW_RESIZE_HINT);
		glfwWindowHint(GLFW_MAXIMIZED, windowHints & WINDOW_MAXIMIZED_HINT);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, windowHints & WINDOW_SCALE_TO_MONITOR_HINT);


		pWindow = glfwCreateWindow((int)dimensions.x, (int)dimensions.y, name.c_str(), NULL, NULL);
		ASSERT(pWindow);
		int w = 0, h = 0;
		glfwGetWindowSize(pWindow, &w, &h);
		dimensions = { (float)w, (float)h };

		glfwMakeContextCurrent(pWindow);

		glfwSwapInterval(1);

		Input::Setup(pWindow);

		ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

		Renderer::Setup(pWindow);
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		Renderer::SetBounds(Vec2(mode->width, mode->height));
	}

	Window::~Window()
	{
		Renderer::Shutdown();
		glfwDestroyWindow(pWindow);
		glfwTerminate();
	}
}