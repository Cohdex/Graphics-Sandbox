#pragma once

#include <vector>

#include "VertexBuffer.h"

namespace sbx
{
	struct VertexAttribute
	{
		int index;
		int size;
		int offset;
	};

	class VertexArray
	{
	private:
		unsigned int m_id;

	public:
		VertexArray();
		~VertexArray();

		void bindVertexBuffer(const VertexBuffer& vertexBuffer, std::vector<VertexAttribute> vertexAttribs);
	};
}
