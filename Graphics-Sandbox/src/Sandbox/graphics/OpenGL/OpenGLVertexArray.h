#pragma once

#include <Sandbox/graphics/VertexArray.h>

namespace sbx
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t m_id;

	public:
		OpenGLVertexArray(uint32_t numElements);
		virtual ~OpenGLVertexArray();

		virtual void bindVertexBuffer(const VertexBuffer& vertexBuffer, int index, int vertexSize) override;
		virtual void bindIndexBuffer(const IndexBuffer& indexBuffer) override;

		virtual void bind() const override;
	};
}
