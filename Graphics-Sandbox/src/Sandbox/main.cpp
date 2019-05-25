#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext = std::make_unique<sbx::RenderingContext>(1920, 1080);

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0,
	};

	sbx::VertexArray vao = renderingContext->createVertexArray(3);
	sbx::VertexBuffer vbo = renderingContext->createVertexBuffer(vertices);
	vao.bindVertexBuffer(vbo, { { 0, 3, 0 } });

	while (renderingContext->running())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderingContext->update();
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, vao.getNumElements());
	}

	return 0;
}
