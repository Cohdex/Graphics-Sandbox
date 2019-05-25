#pragma once

#include <vector>

namespace sbx
{
	class VertexBuffer
	{
	private:
		unsigned int m_id;

	public:
		VertexBuffer(const std::vector<float>& data);
		~VertexBuffer();

		void bind() const;
	};
}
