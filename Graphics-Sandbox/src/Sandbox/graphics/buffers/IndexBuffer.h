#pragma once

#include <vector>

namespace sbx
{
	class IndexBuffer
	{
	private:
		unsigned int m_id;

	public:
		IndexBuffer(const std::vector<unsigned int>& data);
		~IndexBuffer();

		void bind() const;
	};
}
