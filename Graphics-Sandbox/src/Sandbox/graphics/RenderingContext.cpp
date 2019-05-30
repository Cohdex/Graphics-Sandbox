#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>

namespace sbx
{
	static void glfw_error_callback(int error, const char* description)
	{
		std::cout << "GLFW error(" << error << "): " << description << std::endl;
	}

	static void glad_pre_callback(const char* name, void* funcptr, int len_args, ...)
	{
		while (glad_glGetError() != GL_NO_ERROR);
	}

	static void glad_post_callback(const char* name, void* funcptr, int len_args, ...)
	{
		std::vector<unsigned int> errors;
		unsigned int error;
		while ((error = glad_glGetError()) != GL_NO_ERROR)
		{
			errors.push_back(error);
		}
		if (!errors.empty())
		{
			std::cout << "GL function " << name << " caused errors: { ";
			for (unsigned int error : errors)
			{
				std::cout << error << " ";
			}
			std::cout << "}" << std::endl;
		}
	}

	static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	RenderingContext::RenderingContext(int screenWidth, int screenHeight)
		: m_window(nullptr)
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
		glfwWindowHint(GLFW_SAMPLES, 4);
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

		glEnable(GL_MULTISAMPLE);
		glViewport(0, 0, screenWidth, screenHeight);
		glfwSetFramebufferSizeCallback(m_window, glfw_framebuffer_size_callback);

#ifdef GLAD_DEBUG
		glad_set_pre_callback(glad_pre_callback);
		glad_set_post_callback(glad_post_callback);
#endif

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	}

	RenderingContext::~RenderingContext()
	{
		m_vertexArrays.clear();
		m_vertexBuffers.clear();
		m_indexBuffers.clear();
		m_shaders.clear();
		glfwTerminate();
	}

	bool RenderingContext::running()
	{
		return !glfwWindowShouldClose(m_window);
	}

	void RenderingContext::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	int RenderingContext::getWidth() const
	{
		int width;
		glfwGetFramebufferSize(m_window, &width, nullptr);
		return width;
	}

	int RenderingContext::getHeight() const
	{
		int height;
		glfwGetFramebufferSize(m_window, nullptr, &height);
		return height;
	}

	float RenderingContext::getAspectRatio() const
	{
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		return (float)width / (float)height;
	}

	bool RenderingContext::isKeyDown(int keyCode) const
	{
		return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
	}

	VertexArray& RenderingContext::createVertexArray(unsigned int numElements)
	{
		return *m_vertexArrays.emplace_back(new VertexArray(numElements));
	}

	VertexBuffer& RenderingContext::createVertexBuffer(const std::vector<glm::vec2>& data)
	{
		return *m_vertexBuffers.emplace_back(new VertexBuffer(data));
	}

	VertexBuffer& RenderingContext::createVertexBuffer(const std::vector<glm::vec3>& data)
	{
		return *m_vertexBuffers.emplace_back(new VertexBuffer(data));
	}

	VertexBuffer& RenderingContext::createVertexBuffer(const std::vector<glm::vec4>& data)
	{
		return *m_vertexBuffers.emplace_back(new VertexBuffer(data));
	}

	IndexBuffer& RenderingContext::createIndexBuffer(const std::vector<unsigned int>& data)
	{
		return *m_indexBuffers.emplace_back(new IndexBuffer(data));
	}

	Shader& RenderingContext::createShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		return *m_shaders.emplace_back(new Shader(vertexShaderFile, fragmentShaderFile));
	}
}
