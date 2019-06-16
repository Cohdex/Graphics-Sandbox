#pragma once

#include <string>

namespace sbx
{
	class Texture
	{
	protected:
		uint32_t m_textureUnit = 0;

	public:
		virtual ~Texture() = default;

		void setTextureUnit(uint32_t textureUnit) { m_textureUnit = textureUnit; }
		uint32_t getTextureUnit() const { return m_textureUnit; }

		virtual void bind() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Texture2D* create(const std::string& filename);
	};
}
