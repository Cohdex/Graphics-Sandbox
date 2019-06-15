#include "pch.h"
#include <Sandbox/graphics/VertexBuffer.h>

#include "OpenGL/OpenGLVertexBuffer.h"

namespace sbx
{
	static uint32_t getDataTypeComponentCount(const VertexDataType& dataType)
	{
		switch (dataType)
		{
		case VertexDataType::Float: return 1;
		case VertexDataType::Float2: return 2;
		case VertexDataType::Float3: return 3;
		case VertexDataType::Float4: return 4;
		case VertexDataType::Int: return 1;
		case VertexDataType::Int2: return 2;
		case VertexDataType::Int3: return 3;
		case VertexDataType::Int4: return 4;
		case VertexDataType::Mat2: return 2 * 2;
		case VertexDataType::Mat3: return 3 * 3;
		case VertexDataType::Mat4: return 4 * 4;
		default: throw;
		}
	}

	static uint32_t getDataTypeSize(const VertexDataType& dataType)
	{
		switch (dataType)
		{
		case VertexDataType::Float: return 4;
		case VertexDataType::Float2: return 4 * 2;
		case VertexDataType::Float3: return 4 * 3;
		case VertexDataType::Float4: return 4 * 4;
		case VertexDataType::Int: return 4;
		case VertexDataType::Int2: return 4 * 2;
		case VertexDataType::Int3: return 4 * 3;
		case VertexDataType::Int4: return 4 * 4;
		case VertexDataType::Mat2: return 4 * 2 * 2;
		case VertexDataType::Mat3: return 4 * 3 * 3;
		case VertexDataType::Mat4: return 4 * 4 * 4;
		default: throw;
		}
	}

	void BufferLayout::addVertexAttribute(VertexDataType dataType, const std::string& name)
	{
		uint32_t offset = m_stride;
		m_stride += getDataTypeSize(dataType);
		uint32_t componentCount = getDataTypeComponentCount(dataType);
		m_attributes.push_back({ dataType, name, componentCount, offset });
	}

	VertexBuffer* VertexBuffer::create(const float* vertices, size_t size, const BufferLayout& layout)
	{
		return new OpenGLVertexBuffer(vertices, size, layout);
	}
}
