#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>

namespace OpenGLRenderer {

	struct VertexAttribute
	{
		VertexAttribute(uint32_t t, uint32_t c) { type = t; count = c; }
		uint32_t type;
		uint32_t count;
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void SetAttributes(const std::vector<VertexAttribute>& attributes);
		void Bind() { glBindVertexArray(m_RendererID); }
	private:
		uint32_t m_RendererID = 0;
	};
}