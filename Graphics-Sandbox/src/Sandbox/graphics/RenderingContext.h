#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

#include "buffers/VertexArray.h"

namespace sbx
{
	class RenderingContext
	{
	private:
		GLFWwindow* m_window;

		std::vector<std::unique_ptr<VertexArray>> m_vertexArrays;
		std::vector<std::unique_ptr<VertexBuffer>> m_vertexBuffers;

		void init(int screenWidth, int screenHeight);

	public:
		RenderingContext(int screenWidth, int screenHeight);
		~RenderingContext();

		VertexArray& createVertexArray();
		VertexBuffer& createVertexBuffer(void* data, size_t size);
	};
}
