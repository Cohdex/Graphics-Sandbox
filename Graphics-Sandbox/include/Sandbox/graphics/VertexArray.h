#pragma once

#include <cinttypes>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace sbx
{
	class VertexArray
	{
	protected:
		uint32_t m_elementCount;
		bool m_hasIndexBuffer;

		VertexArray(uint32_t elementCount)
			: m_elementCount(elementCount), m_hasIndexBuffer(false)
		{ }

	public:
		virtual ~VertexArray() { }

		uint32_t getElementCount() const { return m_elementCount; }
		bool hasIndexBuffer() const { return m_hasIndexBuffer; }

		virtual void bindVertexBuffer(const VertexBuffer& vertexBuffer) = 0;
		virtual void bindIndexBuffer(const IndexBuffer& indexBuffer) = 0;

		virtual void bind() const = 0;

		static VertexArray* create(uint32_t elementCount);
	};
}
