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

	public:
		RenderingContext(int screenWidth, int screenHeight);
		~RenderingContext();

		bool running();

		void update();

		int getWidth() const;
		int getHeight() const;
		float getAspectRatio() const;

		bool isKeyDown(int keyCode) const;

		VertexArray& createVertexArray(unsigned int numElements);
		VertexBuffer& createVertexBuffer(const std::vector<glm::vec2>& data);
		VertexBuffer& createVertexBuffer(const std::vector<glm::vec3>& data);
		VertexBuffer& createVertexBuffer(const std::vector<glm::vec4>& data);
		IndexBuffer& createIndexBuffer(const std::vector<unsigned int>& data);

		Shader& createShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	};
}
