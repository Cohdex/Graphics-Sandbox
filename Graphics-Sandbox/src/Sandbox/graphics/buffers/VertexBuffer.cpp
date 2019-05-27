#include "pch.h"

#include <Sandbox/graphics/buffers/VertexBuffer.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace sbx
{
	static inline unsigned int createBuffer(const float* data, size_t dataSize)
	{
		unsigned int id;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(float), data, GL_STATIC_DRAW);
		return id;
	}

	VertexBuffer::VertexBuffer(const std::vector<glm::vec2>& data)
		: m_elementSize(2)
	{
		m_id = createBuffer(glm::value_ptr(data[0]), data.size() * m_elementSize);
	}

	VertexBuffer::VertexBuffer(const std::vector<glm::vec3>& data)
		: m_elementSize(3)
	{
		m_id = createBuffer(glm::value_ptr(data[0]), data.size() * m_elementSize);
	}

	VertexBuffer::VertexBuffer(const std::vector<glm::vec4>& data)
		: m_elementSize(4)
	{
		m_id = createBuffer(glm::value_ptr(data[0]), data.size() * m_elementSize);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
}
