#include "pch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace sbx
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, size_t size)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
}
