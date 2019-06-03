#pragma once

#include <Sandbox/graphics/Shader.h>

#include <cinttypes>

namespace sbx
{
	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_id;

	public:
		OpenGLShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

		virtual ~OpenGLShader();

		virtual void bind() override;

		virtual void setUniform(const std::string& name, float value) override;
		virtual void setUniform(const std::string& name, glm::vec2 value) override;
		virtual void setUniform(const std::string& name, glm::vec3 value) override;
		virtual void setUniform(const std::string& name, glm::vec4 value) override;
		virtual void setUniform(const std::string& name, glm::mat4 value) override;
	};
}
