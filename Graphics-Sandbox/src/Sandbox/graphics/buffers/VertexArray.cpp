#include "pch.h"

#include <Sandbox/graphics/buffers/VertexArray.h>

#include <glad/glad.h>

namespace sbx
{
	VertexArray::VertexArray(unsigned int numElements)
		: m_numElements(numElements), m_hasIndexBuffer(false)
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bindVertexBuffer(const VertexBuffer& vertexBuffer, int index)
	{
		bind();
		vertexBuffer.bind();
		int elementSize = vertexBuffer.getElementSize();
		int stride = elementSize * sizeof(float);
		glVertexAttribPointer(index, elementSize, GL_FLOAT, GL_FALSE, stride, static_cast<void*>(0));
		glEnableVertexAttribArray(index);
	}

	void VertexArray::bindIndexBuffer(const IndexBuffer& indexBuffer)
	{
		bind();
		indexBuffer.bind();
		m_hasIndexBuffer = true;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}
}
