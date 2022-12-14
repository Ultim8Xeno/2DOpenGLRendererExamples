#include "Input.h"
#include <iostream>
#include "Renderer.h"

namespace OpenGLRenderer {

	std::unordered_map<uint32_t, uint8_t> Input::Keys;
	std::unordered_map<uint8_t, uint8_t> Input::MouseButtons;
	std::unordered_map<uint8_t, uint8_t> Input::MouseButtonsLast;
	Vec2 Input::MousePos;
	GLFWwindow* pWindow = nullptr;

	void OpenGLRenderer::Input::Setup(GLFWwindow* window)
	{
		pWindow = window;
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Input::Keys[key] = action;
			});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				Input::MouseButtons[button] = action;
			});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				int height = 0;
				glfwGetWindowSize(pWindow, NULL, &height);
				Input::MousePos = Vec2(xpos, height-ypos);
			});
	}

	void Input::Update()
	{
		for (auto& button : Input::MouseButtonsLast)
		{
			if (button.second == GLFW_PRESS)
			{
				if (MouseButtons[button.first])
					MouseButtons[button.first] = GLFW_REPEAT;
				else
					MouseButtons[button.first] = GLFW_RELEASE;
			}
		}
		for (auto& button : Input::MouseButtons)
		{
			MouseButtonsLast[button.first] = button.second;
		}
	}
	uint8_t Input::GetKeyState(uint32_t key)
	{
		return Keys[key];
	}
	uint8_t Input::GetMouseButtonState(uint32_t button)
	{
		return MouseButtons[button];
	}
	Vec2 Input::GetMousePos()
	{
		return MousePos;
	}
}