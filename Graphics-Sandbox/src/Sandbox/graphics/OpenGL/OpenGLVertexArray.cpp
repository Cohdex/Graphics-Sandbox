#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace sbx
{
	OpenGLVertexArray::OpenGLVertexArray(uint32_t numElements)
		: VertexArray(numElements)
	{
		glGenVertexArrays(1, &m_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void OpenGLVertexArray::bindVertexBuffer(const VertexBuffer& vertexBuffer, int index, int vertexSize)
	{
		bind();
		vertexBuffer.bind();
		int stride = vertexSize * sizeof(float);
		glVertexAttribPointer(index, vertexSize, GL_FLOAT, GL_FALSE, stride, static_cast<void*>(0));
		glEnableVertexAttribArray(index);
	}

	void OpenGLVertexArray::bindIndexBuffer(const IndexBuffer& indexBuffer)
	{
		bind();
		indexBuffer.bind();
		m_hasIndexBuffer = true;
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}
}
