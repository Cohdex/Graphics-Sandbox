#include <pch.h>

#include "VertexBuffer.h"

#include <glad/glad.h>

namespace sbx
{
	VertexBuffer::VertexBuffer(void* data, size_t size)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
}
