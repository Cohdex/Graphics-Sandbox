#pragma once

namespace sbx
{
	class VertexBuffer
	{
		friend class VertexArray;

	private:
		unsigned int m_id;

	public:
		VertexBuffer(void* data, size_t size);
		~VertexBuffer();
	};
}
