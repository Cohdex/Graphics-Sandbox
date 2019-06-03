#pragma once

#include <cinttypes>

namespace sbx
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void bind() const = 0;

		static IndexBuffer* create(const uint32_t* indices, size_t size);
	};
}
