#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace sbx
{
	class VertexBuffer
	{
		friend class RenderingContext;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

	private:
		unsigned int m_id;
		int m_elementSize;

		VertexBuffer(const std::vector<glm::vec2>& data);
		VertexBuffer(const std::vector<glm::vec3>& data);
		VertexBuffer(const std::vector<glm::vec4>& data);
	public:
		~VertexBuffer();

		inline int getElementSize() const { return m_elementSize; }

		void bind() const;
	};
}
