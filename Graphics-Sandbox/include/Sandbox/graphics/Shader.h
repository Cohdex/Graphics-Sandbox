#pragma once

#include <string>

#include <glm/glm.hpp>

namespace sbx
{
	class Shader
	{
		friend class RenderingContext;

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

	private:
		unsigned int m_id;

		Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	public:
		~Shader();

		void bind();

		void setUniform(const std::string& name, float value);
		void setUniform(const std::string& name, glm::vec2 value);
		void setUniform(const std::string& name, glm::vec3 value);
		void setUniform(const std::string& name, glm::vec4 value);
		void setUniform(const std::string& name, glm::mat4 value);
	};
}
