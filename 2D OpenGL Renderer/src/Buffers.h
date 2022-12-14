#pragma once
#include <string>
#include <glad/glad.h>

namespace OpenGLRenderer {

	class VertexBuffer
	{
	public:
		VertexBuffer(void* data, uint32_t size);
		~VertexBuffer();
		void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
	private:
		uint32_t m_RendererID = 0;
	};
	
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* data, uint32_t size);
		~IndexBuffer();
		void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
	private:
		uint32_t m_RendererID = 0;
	};
}