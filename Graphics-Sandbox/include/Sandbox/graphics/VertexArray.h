#pragma once

#include <cinttypes>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace sbx
{
	class VertexArray
	{
	protected:
		uint32_t m_numElements;
		bool m_hasIndexBuffer;

		VertexArray(uint32_t numElements)
			: m_numElements(numElements), m_hasIndexBuffer(false)
		{ }

	public:
		virtual ~VertexArray() { }

		uint32_t getNumElements() const { return m_numElements; }
		bool hasIndexBuffer() const { return m_hasIndexBuffer; }

		virtual void bindVertexBuffer(const VertexBuffer& vertexBuffer, int index, int vertexSize) = 0;
		virtual void bindIndexBuffer(const IndexBuffer& indexBuffer) = 0;

		virtual void bind() const = 0;

		static VertexArray* create(uint32_t numElements);
	};
}
