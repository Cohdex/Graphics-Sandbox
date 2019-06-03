#include "pch.h"
#include <Sandbox/graphics/IndexBuffer.h>

#include "OpenGL/OpenGLIndexBuffer.h"

namespace sbx
{
	IndexBuffer* IndexBuffer::create(const uint32_t* indices, size_t size)
	{
		return new OpenGLIndexBuffer(indices, size);
	}
}
