#include "VertexArray.h"
#include <glad/glad.h>

namespace OpenGLRenderer {
	
	static uint32_t TypeToSize(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(float);
		case GL_INT: return sizeof(int);
		case GL_BOOL: return sizeof(bool);
		default:
			return 0;
			break;
		}
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::SetAttributes(const std::vector<VertexAttribute>& attributes)
	{
		uint32_t offset = 0;
		uint32_t stride = 0;
		for (int i = 0; i < attributes.size(); i++)
			stride += attributes[i].count * TypeToSize(attributes[i].type);
		for (int i = 0; i < attributes.size(); i++)
		{
			switch (attributes[i].type)
			{
			case GL_FLOAT:
				glVertexAttribPointer(i, attributes[i].count, attributes[i].type, GL_FALSE, stride, (void*)offset);
				break;
			case GL_INT:
				glVertexAttribIPointer(i, attributes[i].count, attributes[i].type, stride, (void*)offset);
				break;
			default:
				break;
			}
			glEnableVertexAttribArray(i);
			offset += attributes[i].count * TypeToSize(attributes[i].type);
		}
	}
}