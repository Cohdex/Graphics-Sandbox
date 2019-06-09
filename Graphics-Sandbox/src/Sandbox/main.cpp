#include "pch.h"

#include <Sandbox/graphics/RenderingContext.h>
#include <Sandbox/graphics/VertexArray.h>
#include <Sandbox/graphics/Shader.h>
#include <Sandbox/scene/Camera.h>

#include <cinttypes>
#include <random>

int main() {
	std::unique_ptr<sbx::RenderingContext> renderingContext(new sbx::RenderingContext(1920, 1080));

	sbx::Camera camera(glm::vec3(), 0.0f, 0.0f);
	camera.setFov(70.0f);
	camera.setAspectRatio(renderingContext->getAspectRatio());

	std::unique_ptr<sbx::Shader> shader(sbx::Shader::create("res/shaders/test.vs", "res/shaders/test.fs"));

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> barycentrics;
	std::vector<uint32_t> indices;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	int size = 100;
	float scale = 0.1f;
	for (int z = 0; z < size; z++)
	{
		for (int x = 0; x < size; x++)
		{
			vertices.emplace_back(x * scale, 0, z * scale);
			vertices.emplace_back(x * scale, 0, (z + 1) * scale);
			vertices.emplace_back((x + 1) * scale, 0, (z + 1) * scale);
			vertices.emplace_back((x + 1) * scale, 0, z * scale);

			glm::vec3 color(distribution(generator), distribution(generator), distribution(generator));
			colors.push_back(color);
			colors.push_back(color);
			colors.push_back(color);
			colors.push_back(color);

			barycentrics.emplace_back(-1, 1);
			barycentrics.emplace_back(-1, -1);
			barycentrics.emplace_back(1, -1);
			barycentrics.emplace_back(1, 1);

			int baseIndex = (z * size + x) * 4;
			indices.emplace_back(baseIndex + 0);
			indices.emplace_back(baseIndex + 1);
			indices.emplace_back(baseIndex + 2);
			indices.emplace_back(baseIndex + 2);
			indices.emplace_back(baseIndex + 3);
			indices.emplace_back(baseIndex + 0);
		}
	}

	std::unique_ptr<sbx::VertexArray> vao(sbx::VertexArray::create(indices.size()));

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
		camera.position() += camera.getForward() * deltaTime * moveSpeed * movement.z;
		camera.position() += camera.getRight() * deltaTime * moveSpeed * movement.x;
		camera.position() += camera.getUp() * deltaTime * moveSpeed * movement.y;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		shader->bind();
		shader->setUniform("u_projection", camera.getProjectionMatrix());
		shader->setUniform("u_view", camera.getViewMatrix());
		shader->setUniform("u_time", time);

		shader->setUniform("u_model", glm::mat4(1.0f));
		vao->bind();
		if (vao->hasIndexBuffer())
		{
			glDrawElements(GL_TRIANGLES, vao->getNumElements(), GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, vao->getNumElements());
		}
	}

	return 0;
}
