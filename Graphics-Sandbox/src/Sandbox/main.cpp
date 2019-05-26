#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext = std::make_unique<sbx::RenderingContext>(1920, 1080);

	sbx::Shader& shader = renderingContext->createShader("res/shaders/test.vs", "res/shaders/test.fs");

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	std::vector<float> colors = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	};
	std::vector<float> barycentrics = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};

	sbx::VertexArray& vao = renderingContext->createVertexArray(6);

	sbx::VertexBuffer& positionBuffer = renderingContext->createVertexBuffer(vertices);
	vao.bindVertexBuffer(positionBuffer, 0, 3);

	sbx::VertexBuffer& colorBuffer = renderingContext->createVertexBuffer(colors);
	vao.bindVertexBuffer(colorBuffer, 1, 3);

	sbx::VertexBuffer& barycentricBuffer = renderingContext->createVertexBuffer(barycentrics);
	vao.bindVertexBuffer(barycentricBuffer, 2, 2);

	sbx::IndexBuffer& ibo = renderingContext->createIndexBuffer(indices);
	vao.bindIndexBuffer(ibo);

	while (renderingContext->running())
	{
		renderingContext->update();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();

		vao.bind();
		if (vao.hasIndexBuffer())
			glDrawElements(GL_TRIANGLES, vao.getNumElements(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GL_TRIANGLES, 0, vao.getNumElements());

	}

	renderingContext.reset(nullptr);

	return 0;
}
