#pragma once

#include <string>

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
	};
}
