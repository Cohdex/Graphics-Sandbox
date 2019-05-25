#include "pch.h"

#include <Sandbox/graphics/Shader.h>

#include <vector>
#include <fstream>
#include <streambuf>

namespace sbx
{
	static inline unsigned int compileShader(const char* source, unsigned int shaderType)
	{
		unsigned int shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> log(logLength);
			glGetShaderInfoLog(shader, logLength, nullptr, log.data());
			std::cout << "Failed to compile shader: " << log.data() << std::endl;
			glDeleteShader(shader);
			throw;
		}
		return shader;
	}

	static inline std::string readShaderSource(const std::string& shaderFile)
	{
		std::ifstream in(shaderFile);
		std::string source;

		in.seekg(0, std::ios::end);
		source.reserve(in.tellg());
		in.seekg(0, std::ios::beg);

		source.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

		return source;
	}

	Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		m_id = glCreateProgram();

		unsigned int vertexShader = compileShader(readShaderSource(vertexShaderFile).c_str(), GL_VERTEX_SHADER);
		unsigned int fragmentShader = compileShader(readShaderSource(fragmentShaderFile).c_str(), GL_FRAGMENT_SHADER);

		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);

		glLinkProgram(m_id);
		
		glDetachShader(m_id, vertexShader);
		glDetachShader(m_id, fragmentShader);
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			int logLength;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> log(logLength);
			glGetProgramInfoLog(m_id, logLength, nullptr, log.data());
			std::cout << "Failed to link shader: " << log.data() << std::endl;
			glDeleteProgram(m_id);
			throw;
		}
	}
	
	Shader::~Shader()
	{
		glDeleteProgram(m_id);
	}
	
	void Shader::bind()
	{
		glUseProgram(m_id);
	}
}
