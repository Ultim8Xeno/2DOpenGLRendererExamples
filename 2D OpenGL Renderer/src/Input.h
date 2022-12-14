#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "Vector.h"

namespace OpenGLRenderer {

	class Input
	{
	public:
		static void Setup(GLFWwindow* window);
		static void Update();
		static uint8_t GetKeyState(uint32_t key);
		static uint8_t GetMouseButtonState(uint32_t button);
		static Vec2 GetMousePos();
	private:
		static std::unordered_map<uint32_t, uint8_t> Keys;
		static std::unordered_map<uint8_t, uint8_t> MouseButtons;
		static Vec2 MousePos;
		static std::unordered_map<uint8_t, uint8_t> MouseButtonsLast;
	};
}