#include <pch.h>

#include "RenderingContext.h"

namespace sbx
{
	static void glfw_error_callback(int error, const char* description)
	{
		std::cout << "GLFW error(" << error << "): " << description << std::endl;
	}

	RenderingContext::RenderingContext(int screenWidth, int screenHeight)
	{
		init(screenWidth, screenHeight);
	}

	RenderingContext::~RenderingContext()
	{
		m_vertexArrays.clear();
		m_vertexBuffers.clear();
		glfwTerminate();
	}

	void RenderingContext::init(int screenWidth, int screenHeight)
	{
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			throw;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(screenWidth, screenHeight, "Hello world!", nullptr, nullptr);
		if (m_window == nullptr)
		{
			std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
			throw;
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			glfwTerminate();
			throw;
		}

		std::cout << "OpenGL version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
	}

	VertexArray& RenderingContext::createVertexArray()
	{
		auto vertexArray = std::make_unique<VertexArray>();
		m_vertexArrays.push_back(std::move(vertexArray));
		return *m_vertexArrays.back();
	}

	VertexBuffer& RenderingContext::createVertexBuffer(void* data, size_t size)
	{
		auto vertexBuffer = std::make_unique<VertexBuffer>(data, size);
		m_vertexBuffers.push_back(std::move(vertexBuffer));
		return *m_vertexBuffers.back();
	}
}
