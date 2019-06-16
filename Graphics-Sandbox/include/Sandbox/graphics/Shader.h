#pragma once

#include <string>

#include <glm/glm.hpp>

namespace sbx
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;

		virtual void setUniform(const std::string& name, float value) = 0;
		virtual void setUniform(const std::string& name, glm::vec2 value) = 0;
		virtual void setUniform(const std::string& name, glm::vec3 value) = 0;
		virtual void setUniform(const std::string& name, glm::vec4 value) = 0;
		virtual void setUniform(const std::string& name, glm::mat4 value) = 0;
		virtual void setUniform(const std::string& name, int value) = 0;

		static Shader* create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	};
}
