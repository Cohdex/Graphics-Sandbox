#include <pch.h>

#include "VertexArray.h"

#include <glad/glad.h>

namespace sbx
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bindVertexBuffer(const VertexBuffer& vertexBuffer, std::vector<VertexAttribute> vertexAttribs)
	{
		glBindVertexArray(m_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.m_id);
		for (auto attrib : vertexAttribs)
		{
			glVertexAttribPointer(attrib.index, attrib.size, GL_FLOAT, GL_FALSE, attrib.size * sizeof(float), (void*) attrib.offset);
			glEnableVertexAttribArray(attrib.index);
		}
	}
}
