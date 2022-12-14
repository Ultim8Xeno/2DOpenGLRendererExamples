#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vector.h"
#include <string>

// WINDOW_HINTS
#define WINDOW_MAXIMIZED_HINT 1
#define WINDOW_RESIZE_HINT 2
#define WINDOW_SCALE_TO_MONITOR_HINT 4

namespace OpenGLRenderer {
	
	class Window
	{
	public:
		Window(const std::string& name, const Vec2& dim, uint8_t windowHints);
		~Window();

		bool ShouldWindowClose() { return glfwWindowShouldClose(pWindow); }
		GLFWwindow* GetWindow() { return pWindow; }
	private:
		GLFWwindow* pWindow;
		Vec2 dimensions;
	};
}