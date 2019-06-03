#include "pch.h"
#include <Sandbox/graphics/VertexBuffer.h>

#include "OpenGL/OpenGLVertexBuffer.h"

namespace sbx
{
	VertexBuffer* VertexBuffer::create(const float* vertices, size_t size)
	{
		return new OpenGLVertexBuffer(vertices, size);
	}
}
