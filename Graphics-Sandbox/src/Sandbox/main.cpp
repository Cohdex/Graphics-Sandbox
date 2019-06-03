#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>
#include <Sandbox/graphics/VertexArray.h>
#include <Sandbox/graphics/Shader.h>
#include <Sandbox/scene/Camera.h>

#include <cinttypes>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext(new sbx::RenderingContext(1920, 1080));

	sbx::Camera camera(glm::vec3(), 0.0f, 0.0f);
	camera.setFov(70.0f);
	camera.setAspectRatio(renderingContext->getAspectRatio());

	std::unique_ptr<sbx::Shader> shader(sbx::Shader::create("res/shaders/test.vs", "res/shaders/test.fs"));

	std::vector<glm::vec3> vertices = {
		// Front
		{ -0.5f, -0.5f, 0.5f },
		{ 0.5f, -0.5f, 0.5f },
		{ 0.5f, 0.5f, 0.5f },
		{ -0.5f, 0.5f, 0.5f },
		// Back
		{ -0.5f, -0.5f, -0.5f },
		{ 0.5f, -0.5f, -0.5f },
		{ 0.5f, 0.5f, -0.5f },
		{ -0.5f, 0.5f, -0.5f },
		// Right
		{ 0.5f, -0.5f, 0.5f },
		{ 0.5f, -0.5f, -0.5f },
		{ 0.5f, 0.5f, -0.5f },
		{ 0.5f, 0.5f, 0.5f },
		// Left
		{ -0.5f, -0.5f, -0.5f },
		{ -0.5f, -0.5f, 0.5f },
		{ -0.5f, 0.5f, 0.5f },
		{ -0.5f, 0.5f, -0.5f }
	};
	std::vector<glm::vec3> colors = {
		// Front
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f },
		// Back
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.5f },
		{ 0.0f, 0.5f, 1.0f },
		{ 0.5f, 0.5f, 1.0f },
		// Right
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f },
		// Left
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f }
	};
	std::vector<glm::vec2> barycentrics = {
		// Front
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, 1.0f },
		{ -1.0f, 1.0f },
		// Back
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, 1.0f },
		{ -1.0f, 1.0f },
		// Right
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, 1.0f },
		{ -1.0f, 1.0f },
		// Left
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, 1.0f },
		{ -1.0f, 1.0f }
	};
	std::vector<uint32_t> indices = {
		// Front
		0, 1, 2,
		0, 2, 3,
		// Back
		4, 5, 6,
		4, 6, 7,
		// Right
		8, 9, 10,
		8, 10, 11,
		// Left
		12, 13, 14,
		12, 14, 15
	};

	std::unique_ptr<sbx::VertexArray> vao(sbx::VertexArray::create(6 * 4));

	std::unique_ptr<sbx::VertexBuffer> positionBuffer(sbx::VertexBuffer::create(reinterpret_cast<float*>(vertices.data()), vertices.size() * 3));
	vao->bindVertexBuffer(*positionBuffer, 0, 3);

	std::unique_ptr<sbx::VertexBuffer> colorBuffer(sbx::VertexBuffer::create(reinterpret_cast<float*>(colors.data()), colors.size() * 3));
	vao->bindVertexBuffer(*colorBuffer, 1, 3);

	std::unique_ptr<sbx::VertexBuffer> barycentricBuffer(sbx::VertexBuffer::create(reinterpret_cast<float*>(barycentrics.data()), barycentrics.size() * 2));
	vao->bindVertexBuffer(*barycentricBuffer, 2, 2);

	std::unique_ptr<sbx::IndexBuffer> ibo(sbx::IndexBuffer::create(indices.data(), indices.size()));
	vao->bindIndexBuffer(*ibo);

	glEnable(GL_DEPTH_TEST);

	double lastTime = glfwGetTime();
	while (renderingContext->running() && !renderingContext->isKeyDown(GLFW_KEY_ESCAPE))
	{
		float time;
		float deltaTime;
		{
			double currentTime = glfwGetTime();
			time = static_cast<float>(currentTime);
			deltaTime = static_cast<float>(currentTime - lastTime);
			lastTime = currentTime;
		}

		renderingContext->update();

		float pitchRotation = 0.0f;
		float yawRotation = 0.0f;
		if (renderingContext->isKeyDown(GLFW_KEY_UP))
			pitchRotation++;
		if (renderingContext->isKeyDown(GLFW_KEY_DOWN))
			pitchRotation--;
		if (renderingContext->isKeyDown(GLFW_KEY_RIGHT))
			yawRotation++;
		if (renderingContext->isKeyDown(GLFW_KEY_LEFT))
			yawRotation--;

		float rotationSpeed = 50.0f;
		camera.setPitch(camera.getPitch() + deltaTime * rotationSpeed * pitchRotation);
		camera.setYaw(camera.getYaw() + deltaTime * rotationSpeed * yawRotation);

		float forwardMovement = 0.0f;
		float sideMovement = 0.0f;
		float verticalMovement = 0.0f;
		if (renderingContext->isKeyDown(GLFW_KEY_W))
			forwardMovement++;
		if (renderingContext->isKeyDown(GLFW_KEY_S))
			forwardMovement--;
		if (renderingContext->isKeyDown(GLFW_KEY_D))
			sideMovement++;
		if (renderingContext->isKeyDown(GLFW_KEY_A))
			sideMovement--;
		if (renderingContext->isKeyDown(GLFW_KEY_SPACE))
			verticalMovement++;
		if (renderingContext->isKeyDown(GLFW_KEY_LEFT_ALT))
			verticalMovement--;

		float moveSpeed = 0.5f;
		camera.position() += camera.getForward() * deltaTime * moveSpeed * forwardMovement;
		camera.position() += camera.getRight() * deltaTime * moveSpeed * sideMovement;
		camera.position() += camera.getUp() * deltaTime * moveSpeed * verticalMovement;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		shader->bind();
		shader->setUniform("u_projection", camera.getProjectionMatrix());
		shader->setUniform("u_view", camera.getViewMatrix());
		shader->setUniform("u_time", time);

		shader->setUniform("u_model", glm::mat4(1.0f));
		vao->bind();
		if (vao->hasIndexBuffer())
			glDrawElements(GL_TRIANGLES, vao->getNumElements(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GL_TRIANGLES, 0, vao->getNumElements());
	}

	return 0;
}
