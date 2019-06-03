#include "pch.h"
#include <Sandbox/graphics/VertexArray.h>

#include "OpenGL/OpenGLVertexArray.h"

namespace sbx
{
	VertexArray* VertexArray::create(uint32_t numElements)
	{
		return new OpenGLVertexArray(numElements);
	}
}
