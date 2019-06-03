#pragma once

#include <Sandbox/graphics/IndexBuffer.h>

namespace sbx
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t m_id;

	public:
		OpenGLIndexBuffer(const uint32_t* indices, size_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
	};
}
