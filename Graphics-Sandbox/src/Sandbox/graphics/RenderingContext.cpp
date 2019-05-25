#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>

namespace sbx
{
	static void glfw_error_callback(int error, const char* description)
	{
		std::cout << "GLFW error(" << error << "): " << description << std::endl;
	}

	RenderingContext::RenderingContext(int screenWidth, int screenHeight)
		: m_window(nullptr)
	{
		init(screenWidth, screenHeight);
	}

	RenderingContext::~RenderingContext()
	{
		m_vertexArrays.clear();
		m_vertexBuffers.clear();
		m_indexBuffers.clear();
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

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			glfwTerminate();
			throw;
		}

		std::cout << "OpenGL version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
	}

	bool RenderingContext::running()
	{
		return !glfwWindowShouldClose(m_window);
	}

	void RenderingContext::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	VertexArray& RenderingContext::createVertexArray(unsigned int numElements)
	{
		auto vertexArray = std::make_unique<VertexArray>(numElements);
		m_vertexArrays.push_back(std::move(vertexArray));
		return *m_vertexArrays.back();
	}

	VertexBuffer& RenderingContext::createVertexBuffer(const std::vector<float>& data)
	{
		auto vertexBuffer = std::make_unique<VertexBuffer>(data);
		m_vertexBuffers.push_back(std::move(vertexBuffer));
		return *m_vertexBuffers.back();
	}

	IndexBuffer& RenderingContext::createIndexBuffer(const std::vector<unsigned int>& data)
	{
		auto indexBuffer = std::make_unique<IndexBuffer>(data);
		m_indexBuffers.push_back(std::move(indexBuffer));
		return *m_indexBuffers.back();
	}
}
