#pragma once

#include "Sandbox/graphics/Texture.h"

namespace sbx
{
	class OpenGLTexture2D : public Texture2D
	{
	private:
		uint32_t m_id;

	public:
		OpenGLTexture2D(const std::string& filename);

		virtual void bind() const override;
	};
}
