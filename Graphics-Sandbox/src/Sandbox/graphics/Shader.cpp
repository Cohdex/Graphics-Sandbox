#include "pch.h"
#include <Sandbox/graphics/Shader.h>

#include "OpenGL/OpenGLShader.h"

namespace sbx
{
	Shader* Shader::create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		return new OpenGLShader(vertexShaderFile, fragmentShaderFile);
	}
}
