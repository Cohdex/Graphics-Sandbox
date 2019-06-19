#pragma once

#include "Sandbox/graphics/VertexArray.h"

#include <memory>

namespace sbx
{
	class Terrain
	{
	private:
		std::unique_ptr<sbx::VertexArray> m_vertexArray;
		std::unique_ptr<sbx::VertexBuffer> m_vertexBuffer;
		std::unique_ptr<sbx::IndexBuffer> m_indexBuffer;

	public:
		Terrain(int width, int depth, float resolution);

		void draw() const;
	};
}
