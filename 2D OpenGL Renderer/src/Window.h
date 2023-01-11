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
	
	// Initialize Window to create window
	class Window
	{
	public:
		// Constructor, Takes in name of window, dimensions, and any window hints (line 8-10)
		Window(const std::string& name, const Vec2& dim, uint8_t windowHints = 0);
		// Destructor
		~Window();

		// Window Closing Functions
		bool ShouldWindowClose() { return glfwWindowShouldClose(pWindow); }
		void CloseWindow() { glfwSetWindowShouldClose(pWindow, true); }

		// Get GLFW Window
		GLFWwindow* GetWindow() { return pWindow; }
	private:
		// Pointer to GLFW window
		GLFWwindow* pWindow;
		// Dimensions of window
		Vec2 dimensions;
	};
}