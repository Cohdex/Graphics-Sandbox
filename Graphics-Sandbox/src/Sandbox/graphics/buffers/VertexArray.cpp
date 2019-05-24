#include <pch.h>

#include "VertexArray.h"

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

	void VertexArray::bindVertexBuffer(const VertexBuffer& vertexBuffer, std::vector<VertexAttribute> vertexAttribs)
	{
		bind();
		vertexBuffer.bind();
		for (auto attrib : vertexAttribs)
		{
			glVertexAttribPointer(attrib.index, attrib.size, GL_FLOAT, GL_FALSE, attrib.size * sizeof(float), reinterpret_cast<void*>(attrib.offset));
			glEnableVertexAttribArray(attrib.index);
		}
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
