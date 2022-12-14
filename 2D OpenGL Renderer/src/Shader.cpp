#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include "Debug.h"
#include <fstream>
#include <sstream>

namespace OpenGLRenderer {

	Shader::Shader(const std::string& vertShaderfilepath, const std::string& fragShaderfilepath)
	{
		std::string ss[2] = { ReadFile(vertShaderfilepath), ReadFile(fragShaderfilepath) };
		const char* shaderStrings[2] = { ss[0].c_str(), ss[1].c_str() };
		uint32_t so[2] = { 0, 0 };
		GLenum types[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

		for (int i = 0; i < 2; i++)
		{
			so[i] = glCreateShader(types[i]);
			glShaderSource(so[i], 1, &shaderStrings[i], NULL);
			glCompileShader(so[i]);

			// Check for Errors
			int success = 0;
			char infoLog[512];
			glGetShaderiv(so[i], GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(so[i], 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::NUMBER::" << i << "::COMPILATION_FAILED\n" << infoLog << std::endl;
				ASSERT(false);
			}
		}

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, so[0]);
		glAttachShader(m_RendererID, so[1]);
		glLinkProgram(m_RendererID);
		int success = 0;
		char infoLog[512];
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
			ASSERT(false);
		}

		glDetachShader(m_RendererID, so[0]);
		glDetachShader(m_RendererID, so[1]);

		glDeleteShader(so[0]);
		glDeleteShader(so[1]);
		
		glUseProgram(m_RendererID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string Shader::ReadFile(const std::string& filepath)
	{
		std::string result = "";
		std::ifstream file(filepath);
		ASSERT(file.is_open());
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		result = ss.str();
		return result;
	}

	void Shader::SetUniform(void* data, const std::string& location, uint32_t type, uint32_t count)
	{
		int loc = glGetUniformLocation(m_RendererID, location.c_str());
		ASSERT(loc!=-1);
		switch (type)
		{
		case GL_FLOAT:
			glUniform1fv(loc, count, (GLfloat*)data); break;
		case GL_FLOAT_VEC2:
			glUniform2fv(loc, count, (GLfloat*)data); break;
		case GL_FLOAT_VEC3:
			glUniform3fv(loc, count, (GLfloat*)data); break;
		case GL_FLOAT_VEC4:
			glUniform4fv(loc, count, (GLfloat*)data); break;
		case GL_INT:
			glUniform1iv(loc, count, (GLint*)data); break;
		case GL_INT_VEC2:
			glUniform2iv(loc, count, (GLint*)data); break;
		case GL_INT_VEC3:
			glUniform3iv(loc, count, (GLint*)data); break;
		case GL_INT_VEC4:
			glUniform4iv(loc, count, (GLint*)data); break;
		default:
			break;
		}
	}
}