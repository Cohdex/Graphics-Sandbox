#pragma once

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

		VertexBuffer(const std::vector<float>& data);
	public:
		~VertexBuffer();

		void bind() const;
	};
}
