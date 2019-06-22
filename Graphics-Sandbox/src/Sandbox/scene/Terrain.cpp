#include "pch.h"
#include "Sandbox/scene/Terrain.h"

#include "Sandbox/util/Noise.h"

#include <vector>
#include <cmath>
#include <random>

#include <glad/glad.h>

namespace sbx
{
	Terrain::Terrain(int width, int depth, float resolution)
	{
		uint32_t xVertCount = static_cast<uint32_t>(std::ceilf(width * resolution));
		uint32_t zVertCount = static_cast<uint32_t>(std::ceilf(depth * resolution));
		float scale = 1.0f / resolution;

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
		std::unique_ptr<sbx::Noise> noise(new sbx::SimplexNoise());
		std::map<uint64_t, glm::vec3> colorMap;
		for (uint32_t z = 0; z < zVertCount; z++)
		{
			for (uint32_t x = 0; x < xVertCount; x++)
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

				float p0x = x0 * scale;
				float p0z = z0 * scale;
				float p1x = x1 * scale;
				float p1z = z1 * scale;

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
					x /= 4;
					z /= 4;
					double persistence = 0.5;
					int octaves = 6;
					double frequency = 1;
					double amplitude = 1;
					double total = 0;
					double max = 0;
					for (int i = 0; i < octaves; i++)
					{
						total += noise->noise(x * frequency, z * frequency) * amplitude;
						max += amplitude;
						amplitude *= persistence;
						frequency *= 2;
					}
					return static_cast<float>(total / max);
				};

				pushFloat3(p0x, height(p0x, p0z), p0z);
				pushFloat2(0.0f, 0.0f);
				pushVec3(colorUL);
				pushVec3(colorUR);
				pushVec3(colorLL);
				pushVec3(colorLR);

				pushFloat3(p0x, height(p0x, p1z), p1z);
				pushFloat2(0.0f, 1.0f);
				pushVec3(colorUL);
				pushVec3(colorUR);
				pushVec3(colorLL);
				pushVec3(colorLR);

				pushFloat3(p1x, height(p1x, p1z), p1z);
				pushFloat2(1.0f, 1.0f);
				pushVec3(colorUL);
				pushVec3(colorUR);
				pushVec3(colorLL);
				pushVec3(colorLR);

				pushFloat3(p1x, height(p1x, p0z), p0z);
				pushFloat2(1.0f, 0.0f);
				pushVec3(colorUL);
				pushVec3(colorUR);
				pushVec3(colorLL);
				pushVec3(colorLR);

				int baseIndex = (x + z * xVertCount) * 4;
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

		m_vertexArray.reset(sbx::VertexArray::create(static_cast<uint32_t>(indices.size())));

		m_vertexBuffer.reset(sbx::VertexBuffer::create(vertices.data(), vertices.size(), layout));
		m_vertexArray->bindVertexBuffer(*m_vertexBuffer);

		m_indexBuffer.reset(sbx::IndexBuffer::create(indices.data(), indices.size()));
		m_vertexArray->bindIndexBuffer(*m_indexBuffer);
	}

	void Terrain::draw() const
	{
		m_vertexArray->bind();
		glDrawElements(GL_TRIANGLES, m_vertexArray->getElementCount(), GL_UNSIGNED_INT, nullptr);
	}
}
