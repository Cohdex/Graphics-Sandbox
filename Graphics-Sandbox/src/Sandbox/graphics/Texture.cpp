#include "pch.h"
#include "Sandbox/graphics/Texture.h"

#include "OpenGL/OpenGLTexture.h"

namespace sbx
{
	Texture2D* Texture2D::create(const std::string& filename)
	{
		return new OpenGLTexture2D(filename);
	}
}
