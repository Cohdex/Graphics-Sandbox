#include "pch.h"
#include <Sandbox/graphics/VertexArray.h>

#include "OpenGL/OpenGLVertexArray.h"

namespace sbx
{
	VertexArray* VertexArray::create(uint32_t elementCount, const Shader& shader)
	{
		return new OpenGLVertexArray(elementCount, shader);
	}
}
