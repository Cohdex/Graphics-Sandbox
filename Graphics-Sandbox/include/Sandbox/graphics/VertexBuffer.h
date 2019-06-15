#pragma once

#include <string>
#include <vector>

namespace sbx
{
	enum class VertexDataType : int8_t
	{
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat2, Mat3, Mat4
	};

	struct VertexAttribute
	{
		const VertexDataType dataType;
		const std::string name;
		const uint32_t componentCount;
		const uint32_t offset;
	};

	class BufferLayout
	{
	private:
		std::vector<VertexAttribute> m_attributes;
		uint32_t m_stride = 0;

	public:
		void addVertexAttribute(VertexDataType dataType, const std::string& name);

		uint32_t getStride() const { return m_stride; };

		std::vector<VertexAttribute>::const_iterator begin() const { return m_attributes.cbegin(); }
		std::vector<VertexAttribute>::const_iterator end() const { return m_attributes.cend(); }
	};

	class VertexBuffer
	{
	protected:
		BufferLayout m_layout;

		VertexBuffer(const BufferLayout& layout)
			: m_layout(layout)
		{
		}

	public:
		const BufferLayout& getBufferLayout() const { return m_layout; }

		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;

		static VertexBuffer* create(const float* vertices, size_t size, const BufferLayout& layout);
	};
}
