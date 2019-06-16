#pragma once

#include <Sandbox/graphics/VertexArray.h>

#include "OpenGLShader.h"

namespace sbx
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t m_id;

	public:
		OpenGLVertexArray(uint32_t elementCount);
		virtual ~OpenGLVertexArray();

		virtual void bindVertexBuffer(const VertexBuffer& vertexBuffer) override;
		virtual void bindIndexBuffer(const IndexBuffer& indexBuffer) override;

		virtual void bind() const override;
	};
}
