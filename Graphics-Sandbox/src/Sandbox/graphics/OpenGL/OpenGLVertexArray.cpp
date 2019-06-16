#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace sbx
{
	static uint32_t getGLDataType(VertexDataType dataType)
	{
		switch (dataType)
		{
		case VertexDataType::Float:
		case VertexDataType::Float2:
		case VertexDataType::Float3:
		case VertexDataType::Float4:
		case VertexDataType::Mat2:
		case VertexDataType::Mat3:
		case VertexDataType::Mat4:
			return GL_FLOAT;
		case VertexDataType::Int:
		case VertexDataType::Int2:
		case VertexDataType::Int3:
		case VertexDataType::Int4:
			return GL_INT;
		default: throw;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray(uint32_t elementCount)
		: VertexArray(elementCount)
	{
		glGenVertexArrays(1, &m_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void OpenGLVertexArray::bindVertexBuffer(const VertexBuffer& vertexBuffer)
	{
		bind();
		vertexBuffer.bind();
		uint32_t index = 0;
		for (const auto& attribute : vertexBuffer.getBufferLayout())
		{
			int32_t componentCount = attribute.componentCount;
			uint32_t type = getGLDataType(attribute.dataType);
			int32_t stride = vertexBuffer.getBufferLayout().getStride();
			void* offset = static_cast<void*>(static_cast<uint8_t*>(0) + attribute.offset);

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, componentCount, type, GL_FALSE, stride, offset);
			index++;
		}
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
