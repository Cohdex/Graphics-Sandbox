#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace sbx
{
	class VertexArray
	{
		friend class RenderingContext;

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

	private:
		unsigned int m_id;
		unsigned int m_numElements;
		bool m_hasIndexBuffer;

		VertexArray(unsigned int numElements);
	public:
		~VertexArray();

		unsigned int getNumElements() const { return m_numElements; }
		bool hasIndexBuffer() const { return m_hasIndexBuffer; }

		void bindVertexBuffer(const VertexBuffer& vertexBuffer, int index);
		void bindIndexBuffer(const IndexBuffer& indexBuffer);

		void bind() const;
	};
}
