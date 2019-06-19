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

	sbx::BufferLayout layout;
	layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_position");
	layout.addVertexAttribute(sbx::VertexDataType::Float2, "in_texcoord");
	layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_colorUL");
	layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_colorUR");
	layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_colorLL");
	layout.addVertexAttribute(sbx::VertexDataType::Float3, "in_colorLR");

	std::vector<float> vertices;
	std::vector<uint32_t> indices;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	std::map<uint64_t, glm::vec3> colorMap;
	std::unique_ptr<sbx::Noise> noise(new sbx::SimplexNoise());
	double noiseMin = 1.0;
	double noiseMax = -1.0;
	for (int i = 0; i < 1000; i++)
	{
		double noiseSample = std::uniform_real_distribution<double>(0.0, 256.0)(generator);
		double noiseVal = noise->noise(noiseSample);
		noiseMin = glm::min(noiseMin, noiseVal);
		noiseMax = glm::max(noiseMax, noiseVal);
	}
	std::cout << "noiseMin: " << noiseMin << ", noiseMax: " << noiseMax << std::endl;
	uint32_t size = 100;
	float scale = 0.1f;
	for (uint32_t z = 0; z < size; z++)
	{
		for (uint32_t x = 0; x < size; x++)
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
			auto pushVec3 = [&vertices](const glm::vec3& v) {
				vertices.emplace_back(v.x);
				vertices.emplace_back(v.y);
				vertices.emplace_back(v.z);
			};

			glm::vec3 colorUL(distribution(generator), distribution(generator), distribution(generator));
			glm::vec3 colorUR(distribution(generator), distribution(generator), distribution(generator));
			glm::vec3 colorLL(distribution(generator), distribution(generator), distribution(generator));
			glm::vec3 colorLR(distribution(generator), distribution(generator), distribution(generator));

			colorUL = glm::vec3(1.0f, 0.0f, 0.0f);
			colorUR = glm::vec3(0.0f, 1.0f, 0.0f);
			colorLL = glm::vec3(0.0f, 0.0f, 1.0f);
			colorLR = glm::vec3(1.0f, 1.0f, 0.0f);

			uint32_t x0 = x;
			uint32_t x1 = x + 1;
			uint32_t z0 = z;
			uint32_t z1 = z + 1;

			auto createKey = [](uint32_t x, uint32_t z) {
				return ((uint64_t)x) << 32 | (uint64_t)z;
			};

			auto getColor = [&colorMap, &generator, &distribution](uint64_t key) {
				auto& foundColor = colorMap.find(key);
				glm::vec3 color;
				if (foundColor == colorMap.end())
				{
					color = glm::vec3(distribution(generator), distribution(generator), distribution(generator));
					colorMap[key] = color;
				}
				else
					color = foundColor->second;
				return color;
			};

			colorUL = getColor(createKey(x0, z0));
			colorUR = getColor(createKey(x1, z0));
			colorLL = getColor(createKey(x0, z1));
			colorLR = getColor(createKey(x1, z1));

			auto height = [&noise](float x, float z) {
				float amplitude = 8;
				float frequency = 1;
				double sum = 0;
				for (int i = 0; i < 8; i++)
				{
					sum += noise->noise(x / frequency, z / frequency) * amplitude;
					amplitude /= 2;
					frequency *= 2;
				}
				//return (float)(sum / 8);
				return static_cast<float>(noise->noise(x, z));
			};

			pushFloat3(x0 * scale, height(x0 * scale, z0 * scale), z0 * scale);
			pushFloat2(0.0f, 0.0f);
			pushVec3(colorUL);
			pushVec3(colorUR);
			pushVec3(colorLL);
			pushVec3(colorLR);

			pushFloat3(x0 * scale, height(x0 * scale, z1 * scale), z1 * scale);
			pushFloat2(0.0f, 1.0f);
			pushVec3(colorUL);
			pushVec3(colorUR);
			pushVec3(colorLL);
			pushVec3(colorLR);
			
			pushFloat3(x1 * scale, height(x1 * scale, z1 * scale), z1 * scale);
			pushFloat2(1.0f, 1.0f);
			pushVec3(colorUL);
			pushVec3(colorUR);
			pushVec3(colorLL);
			pushVec3(colorLR);
			
			pushFloat3(x1 * scale, height(x1 * scale, z0 * scale), z0 * scale);
			pushFloat2(1.0f, 0.0f);
			pushVec3(colorUL);
			pushVec3(colorUR);
			pushVec3(colorLL);
			pushVec3(colorLR);

			int baseIndex = (x + z * size) * 4;
			if ((x + z) % 2 == 0)
			{
				indices.emplace_back(baseIndex + 0);
				indices.emplace_back(baseIndex + 1);
				indices.emplace_back(baseIndex + 2);
				indices.emplace_back(baseIndex + 2);
				indices.emplace_back(baseIndex + 3);
				indices.emplace_back(baseIndex + 0);
			}
			else
			{
				indices.emplace_back(baseIndex + 1);
				indices.emplace_back(baseIndex + 2);
				indices.emplace_back(baseIndex + 3);
				indices.emplace_back(baseIndex + 3);
				indices.emplace_back(baseIndex + 0);
				indices.emplace_back(baseIndex + 1);
			}
		}
	}

	std::unique_ptr<sbx::VertexArray> vao(sbx::VertexArray::create(static_cast<uint32_t>(indices.size())));

	std::unique_ptr<sbx::VertexBuffer> positionBuffer(sbx::VertexBuffer::create(vertices.data(), vertices.size(), layout));
	vao->bindVertexBuffer(*positionBuffer);

	std::unique_ptr<sbx::IndexBuffer> ibo(sbx::IndexBuffer::create(indices.data(), indices.size()));
	vao->bindIndexBuffer(*ibo);

	std::unique_ptr<sbx::Terrain> terrain(new sbx::Terrain(50, 50, 10));

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
		vao->bind();
		if (vao->hasIndexBuffer())
		{
			//glDrawElements(GL_TRIANGLES, vao->getElementCount(), GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, vao->getElementCount());
		}

		terrain->draw();
	}

	return 0;
}
