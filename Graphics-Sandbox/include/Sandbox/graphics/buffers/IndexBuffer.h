#pragma once

#include <vector>

namespace sbx
{
	class IndexBuffer
	{
		friend class RenderingContext;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

	private:
		unsigned int m_id;

		IndexBuffer(const std::vector<unsigned int>& data);
	public:
		~IndexBuffer();

		void bind() const;
	};
}
