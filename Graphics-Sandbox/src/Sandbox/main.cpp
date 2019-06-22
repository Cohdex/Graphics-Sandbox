#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>
#include <Sandbox/graphics/VertexArray.h>
#include <Sandbox/graphics/Shader.h>
#include <Sandbox/graphics/Texture.h>
#include <Sandbox/scene/Camera.h>
#include <Sandbox/scene/Terrain.h>
#include <Sandbox/util/Noise.h>

#include <cinttypes>
#include <random>
#include <map>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext(new sbx::RenderingContext(1920, 1080));

	sbx::Camera camera(glm::vec3(), 0.0f, 0.0f);
	camera.setFov(70.0f);
	camera.setAspectRatio(renderingContext->getAspectRatio());

	std::unique_ptr<sbx::Shader> shader(sbx::Shader::create("res/shaders/test.vs", "res/shaders/test.fs"));

	std::unique_ptr<sbx::Texture2D> texture(sbx::Texture2D::create("res/textures/tile.png"));

	std::unique_ptr<sbx::Terrain> terrain(new sbx::Terrain(50, 50, 2));

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
		{
			pitchRotation++;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_DOWN))
		{
			pitchRotation--;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_RIGHT))
		{
			yawRotation++;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_LEFT))
		{
			yawRotation--;
		}

		float rotationSpeed = 50.0f;
		camera.setPitch(camera.getPitch() + deltaTime * rotationSpeed * pitchRotation);
		camera.setYaw(camera.getYaw() + deltaTime * rotationSpeed * yawRotation);

		glm::vec3 movement(0.0f);
		if (renderingContext->isKeyDown(GLFW_KEY_W))
		{
			movement.z++;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_S))
		{
			movement.z--;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_D))
		{
			movement.x++;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_A))
		{
			movement.x--;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_SPACE))
		{
			movement.y++;
		}
		if (renderingContext->isKeyDown(GLFW_KEY_C))
		{
			movement.y--;
		}

		float movementAmplitude = glm::length(movement);
		if (movementAmplitude > 1.0f)
		{
			movement /= movementAmplitude;
		}

		float moveSpeed = 1.0f;
		if (renderingContext->isKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			moveSpeed = 2.5f;
		}

		camera.position() += camera.getForward() * deltaTime * moveSpeed * movement.z;
		camera.position() += camera.getRight() * deltaTime * moveSpeed * movement.x;
		camera.position() += camera.getUp() * deltaTime * moveSpeed * movement.y;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		shader->bind();
		shader->setUniform("u_projection", camera.getProjectionMatrix());
		shader->setUniform("u_view", camera.getViewMatrix());
		shader->setUniform("u_texture", 0);
		shader->setUniform("u_model", glm::mat4(1.0f));
		texture->bind();

		terrain->draw();
	}

	return 0;
}
