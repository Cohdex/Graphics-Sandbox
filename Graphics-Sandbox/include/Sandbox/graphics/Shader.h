#pragma once

#include <string>

namespace sbx
{
	class Shader
	{
	private:
		unsigned int m_id;

	public:
		Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		~Shader();

		void bind();
	};
}
