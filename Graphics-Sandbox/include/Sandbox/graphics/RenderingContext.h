#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

#include "buffers/VertexArray.h"
#include "Shader.h"

namespace sbx
{
	class RenderingContext
	{
	private:
		GLFWwindow* m_window;

		std::vector<std::unique_ptr<VertexArray>> m_vertexArrays;
		std::vector<std::unique_ptr<VertexBuffer>> m_vertexBuffers;
		std::vector<std::unique_ptr<IndexBuffer>> m_indexBuffers;
		std::vector<std::unique_ptr<Shader>> m_shaders;

		void init(int screenWidth, int screenHeight);

	public:
		RenderingContext(int screenWidth, int screenHeight);
		~RenderingContext();

		bool running();

		void update();

		VertexArray& createVertexArray(unsigned int numElements);
		VertexBuffer& createVertexBuffer(const std::vector<float>& data);
		IndexBuffer& createIndexBuffer(const std::vector<unsigned int>& data);

		Shader& createShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	};
}
