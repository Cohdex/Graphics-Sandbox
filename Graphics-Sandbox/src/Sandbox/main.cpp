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

	sbx::BufferLayout layout;
	layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_position");
	//layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_color");
	//layout.addVertexAttribute(sbx::VertexDataType::Float2, "in_barycentric");

	std::vector<float> vertices;
	std::vector<uint32_t> indices;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	int size = 100;
	float scale = 0.1f;
	for (int z = 0; z < size; z++)
	{
		for (int x = 0; x < size; x++)
		{
			auto pushFloat2 = [&vertices](float x, float y) {
				vertices.emplace_back(x);
				vertices.emplace_back(y);
			};
			auto pushFloat3 = [&vertices](float x, float y, float z) {
				vertices.emplace_back(x);
				vertices.emplace_back(y);
				vertices.emplace_back(z);
			};

			pushFloat3(x * scale, 0, z * scale);
			pushFloat3(x * scale, 0, (z + 1) * scale);
			pushFloat3((x + 1) * scale, 0, (z + 1) * scale);
			pushFloat3((x + 1) * scale, 0, z * scale);

			glm::vec3 color(distribution(generator), distribution(generator), distribution(generator));
			//pushFloat3(color.x, color.y, color.z);
			//pushFloat3(color.x, color.y, color.z);
			//pushFloat3(color.x, color.y, color.z);
			//pushFloat3(color.x, color.y, color.z);

			//pushFloat2(-1.0f, -1.0f);
			//pushFloat2(-1.0f, 1.0f);
			//pushFloat2(1.0f, 1.0f);
			//pushFloat2(1.0f, -1.0f);

			int baseIndex = (z * size + x) * 4;
			indices.emplace_back(baseIndex + 0);
			indices.emplace_back(baseIndex + 1);
			indices.emplace_back(baseIndex + 2);
			indices.emplace_back(baseIndex + 2);
			indices.emplace_back(baseIndex + 3);
			indices.emplace_back(baseIndex + 0);
		}
	}

	std::unique_ptr<sbx::VertexArray> vao(sbx::VertexArray::create(static_cast<uint32_t>(indices.size())));

	std::unique_ptr<sbx::VertexBuffer> positionBuffer(sbx::VertexBuffer::create(vertices.data(), vertices.size(), layout));
	vao->bindVertexBuffer(*positionBuffer);

	std::unique_ptr<sbx::IndexBuffer> ibo(sbx::IndexBuffer::create(indices.data(), indices.size()));
	vao->bindIndexBuffer(*ibo);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
			glDrawElements(GL_TRIANGLES, vao->getElementCount(), GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, vao->getElementCount());
		}
	}

	return 0;
}
