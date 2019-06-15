#pragma once

#include <Sandbox/graphics/VertexBuffer.h>

namespace sbx
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t m_id;

	public:
		OpenGLVertexBuffer(const float* vertices, size_t size, const BufferLayout& layout);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
	};
}
