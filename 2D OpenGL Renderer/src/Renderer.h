#pragma once
#include "Vector.h"
#include "Window.h"
#include "Debug.h"
#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Texture.h"

namespace OpenGLRenderer {

	class Renderer
	{
	public:
		static void Setup(GLFWwindow* window);
		static void Shutdown();
		static void ClearColor(const Vec4& color);
		static void BeginDraw();
		static void EndDraw();
		static void DrawQuad(const Vec3& pos, const Vec2& dim, const Vec4& col, float rot = 0.0f);
		static void DrawTexture(const Vec3& pos, const Vec2& dim, Texture* tex, const Vec4& col = Vec4(1.0f, 1.0f, 1.0f, 1.0f), float rot = 0.0f);
		static void DrawFromSpriteSheet(const Vec3& pos, const Vec2& dim, Texture* tex, const Vec2& startingTexPos,
			const Vec2& spriteSize, const Vec4& col = Vec4(1.0f, 1.0f, 1.0f, 1.0f), float rot = 0.0f);
		static void DrawFromSpriteSheet(const Vec3& pos, const Vec2& dim, uint32_t texId, const Vec2& textureSize,
			const Vec2& startingTexPos, const Vec2& spriteSize, const Vec4& col = Vec4(1.0f, 1.0f, 1.0f, 1.0f), float rot = 0.0f);
		static void Write(const std::string& text, const Vec3& pos, float scale = 1.0f, const Vec4& col = Vec4(1.0f, 1.0f, 1.0f, 1.0f), float rot = 0.0f);
		static void DrawLine(const Vec2& start, const Vec2& end, const Vec4& col, float width, float zIndex = 0.0f);
		static void SetBounds(const Vec2& bounds);
		static float GetDT();
	private:
		static void Flush();
	};
}