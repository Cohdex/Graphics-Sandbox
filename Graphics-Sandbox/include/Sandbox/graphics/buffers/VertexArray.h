#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace sbx
{
	struct VertexAttribute
	{
		int index;
		int size;
		size_t offset;
	};

	class VertexArray
	{
	private:
		unsigned int m_id;
		unsigned int m_numElements;
		bool m_hasIndexBuffer;

	public:
		VertexArray(unsigned int numElements);
		~VertexArray();

		unsigned int getNumElements() const { return m_numElements; }
		bool hasIndexBuffer() const { return m_hasIndexBuffer; }

		void bindVertexBuffer(const VertexBuffer& vertexBuffer, std::vector<VertexAttribute> vertexAttribs);
		void bindIndexBuffer(const IndexBuffer& indexBuffer);

		void bind() const;
	};
}