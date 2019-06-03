#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>
#include <Sandbox/graphics/VertexArray.h>
#include <Sandbox/graphics/Shader.h>
#include <Sandbox/scene/Camera.h>

#include <cinttypes>

#include <glm/gtc/type_ptr.hpp>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext(new sbx::RenderingContext(1920, 1080));

	sbx::Camera camera(glm::vec3(), 0.0f, 0.0f);
	camera.setFov(70.0f);
	camera.setAspectRatio(renderingContext->getAspectRatio());

	std::unique_ptr<sbx::Shader> shader(sbx::Shader::create("res/shaders/test.vs", "res/shaders/test.fs"));

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
	std::vector<uint32_t> indices = {
		0, 1, 2,
		0, 2, 3
	};

	std::unique_ptr<sbx::VertexArray> vao(sbx::VertexArray::create(6));

	std::unique_ptr<sbx::VertexBuffer> positionBuffer(sbx::VertexBuffer::create(glm::value_ptr(vertices[0]), vertices.size()));
	vao->bindVertexBuffer(*positionBuffer, 0, 3);

	std::unique_ptr<sbx::VertexBuffer> colorBuffer(sbx::VertexBuffer::create(glm::value_ptr(colors[0]), colors.size()));
	vao->bindVertexBuffer(*colorBuffer, 1, 3);

	std::unique_ptr<sbx::VertexBuffer> barycentricBuffer(sbx::VertexBuffer::create(glm::value_ptr(barycentrics[0]), barycentrics.size()));
	vao->bindVertexBuffer(*barycentricBuffer, 2, 2);

	std::unique_ptr<sbx::IndexBuffer> ibo(sbx::IndexBuffer::create(indices.data(), indices.size()));
	vao->bindIndexBuffer(*ibo);

	glDisable(GL_CULL_FACE);

	double lastTime = glfwGetTime();
	while (renderingContext->running() && !renderingContext->isKeyDown(GLFW_KEY_ESCAPE))
	{
		double currentTime = glfwGetTime();
		float deltaTime = (float)(currentTime - lastTime);
		lastTime = currentTime;

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
		camera.setPitch(glm::mod(camera.getPitch() + deltaTime * rotationSpeed * pitchRotation, 360.0f));
		camera.setYaw(glm::mod(camera.getYaw() + deltaTime * rotationSpeed * yawRotation, 360.0f));

		float forwardMovement = 0.0f;
		float sideMovement = 0.0f;
		if (renderingContext->isKeyDown(GLFW_KEY_W))
			forwardMovement++;
		if (renderingContext->isKeyDown(GLFW_KEY_S))
			forwardMovement--;
		if (renderingContext->isKeyDown(GLFW_KEY_D))
			sideMovement++;
		if (renderingContext->isKeyDown(GLFW_KEY_A))
			sideMovement--;

		float moveSpeed = 0.5f;
		camera.position() += camera.getForward() * deltaTime * moveSpeed * forwardMovement;
		camera.position() += camera.getRight() * deltaTime * moveSpeed * sideMovement;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->bind();
		shader->setUniform("u_projection", camera.getProjectionMatrix());
		shader->setUniform("u_view", camera.getViewMatrix());
		shader->setUniform("time", static_cast<float>(glfwGetTime()));

		shader->setUniform("u_model", glm::mat4(1.0f));
		vao->bind();
		if (vao->hasIndexBuffer())
			glDrawElements(GL_TRIANGLES, vao->getNumElements(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GL_TRIANGLES, 0, vao->getNumElements());
	}

	renderingContext.reset(nullptr);

	return 0;
}
