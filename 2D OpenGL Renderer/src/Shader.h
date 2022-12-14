#pragma once
#include <string>
#include <glad/glad.h>

namespace OpenGLRenderer {

	class Shader
	{
	public:
		Shader(const std::string& vertShaderfilepath, const std::string& fragShaderfilepath);
		~Shader();
		void Bind() { glUseProgram(m_RendererID); }
		std::string ReadFile(const std::string& filepath);
		void SetUniform(void* data, const std::string& location, uint32_t type, uint32_t count);
	private:
		uint32_t m_RendererID = 0;
	};
}