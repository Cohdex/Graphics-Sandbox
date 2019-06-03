#pragma once

#include <cinttypes>

namespace sbx
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }

		virtual void bind() const = 0;

		static VertexBuffer* create(const float* vertices, size_t size);
	};
}
