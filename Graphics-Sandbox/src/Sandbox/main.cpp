#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext = std::make_unique<sbx::RenderingContext>(1920, 1080);

	sbx::Shader& shader = renderingContext->createShader("res/shaders/test.vs", "res/shaders/test.fs");

	std::vector<glm::vec3> vertices = {
		{ -0.5f, -0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f }
	};
	std::vector<glm::vec3> colors = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f }
	};
	std::vector<glm::vec2> barycentrics = {
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, 1.0f },
		{ -1.0f, 1.0f }
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};

	sbx::VertexArray& vao = renderingContext->createVertexArray(6);

	sbx::VertexBuffer& positionBuffer = renderingContext->createVertexBuffer(vertices);
	vao.bindVertexBuffer(positionBuffer, 0);

	sbx::VertexBuffer& colorBuffer = renderingContext->createVertexBuffer(colors);
	vao.bindVertexBuffer(colorBuffer, 1);

	sbx::VertexBuffer& barycentricBuffer = renderingContext->createVertexBuffer(barycentrics);
	vao.bindVertexBuffer(barycentricBuffer, 2);

	sbx::IndexBuffer& ibo = renderingContext->createIndexBuffer(indices);
	vao.bindIndexBuffer(ibo);

	while (renderingContext->running())
	{
		renderingContext->update();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		shader.setUniform("time", static_cast<float>(glfwGetTime()));

		vao.bind();
		if (vao.hasIndexBuffer())
			glDrawElements(GL_TRIANGLES, vao.getNumElements(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GL_TRIANGLES, 0, vao.getNumElements());

	}

	renderingContext.reset(nullptr);

	return 0;
}
