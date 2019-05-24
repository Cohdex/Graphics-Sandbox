#include <pch.h>

#include <Sandbox/graphics/RenderingContext.h>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext = std::make_unique<sbx::RenderingContext>(1920, 1080);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0,
	};

	sbx::VertexArray vao = renderingContext->createVertexArray();
	sbx::VertexBuffer vbo = renderingContext->createVertexBuffer(vertices, sizeof(vertices));
	vao.bindVertexBuffer(vbo, { { 0, 3, 0 } });

	return 0;
}
