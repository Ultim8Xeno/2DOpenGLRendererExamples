#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Vector.h"

namespace OpenGLRenderer
{
	class Texture
	{
	public:
		Texture(const std::string& filepath);
		Texture(void* data, int width, int height);
		~Texture();

		uint32_t GetID() const { return m_RendererID; }
		const Vec2& GetSize() const { return m_TexSize; }
	private:
		uint32_t m_RendererID = 0;
		Vec2 m_TexSize = Vec2(0.0f, 0.0f);
	};
}