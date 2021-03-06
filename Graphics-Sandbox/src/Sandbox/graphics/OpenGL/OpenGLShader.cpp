#include "pch.h"
#include "OpenGLShader.h"

#include <vector>
#include <fstream>
#include <streambuf>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace sbx
{
	static inline uint32_t compileShader(const char* source, uint32_t shaderType, const std::string& filename)
	{
		uint32_t shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		int32_t success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int32_t logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> log(logLength);
			glGetShaderInfoLog(shader, logLength, nullptr, log.data());
			std::cout << "Failed to compile shader " << filename << ":" << std::endl << log.data() << std::endl;
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

	OpenGLShader::OpenGLShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		m_id = glCreateProgram();

		uint32_t vertexShader = compileShader(readShaderSource(vertexShaderFile).c_str(), GL_VERTEX_SHADER, vertexShaderFile);
		uint32_t fragmentShader = compileShader(readShaderSource(fragmentShaderFile).c_str(), GL_FRAGMENT_SHADER, fragmentShaderFile);

		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);

		glLinkProgram(m_id);

		glDetachShader(m_id, vertexShader);
		glDetachShader(m_id, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int32_t success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			int32_t logLength;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> log(logLength);
			glGetProgramInfoLog(m_id, logLength, nullptr, log.data());
			std::cout << "Failed to link shader: " << log.data() << std::endl;
			glDeleteProgram(m_id);
			throw;
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_id);
	}

	static inline int32_t getUniformLocation(uint32_t programId, const std::string& name)
	{
		return glGetUniformLocation(programId, name.c_str());
	}

	void OpenGLShader::setUniform(const std::string& name, float value)
	{
		glUniform1fv(getUniformLocation(m_id, name), 1, &value);
	}

	void OpenGLShader::setUniform(const std::string& name, glm::vec2 value)
	{
		glUniform2fv(getUniformLocation(m_id, name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(const std::string& name, glm::vec3 value)
	{
		glUniform3fv(getUniformLocation(m_id, name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(const std::string& name, glm::vec4 value)
	{
		glUniform4fv(getUniformLocation(m_id, name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(getUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(const std::string& name, int value)
	{
		glUniform1iv(getUniformLocation(m_id, name), 1, &value);
	}
}
