#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sbx
{
	class RenderingContext
	{
	private:
		GLFWwindow* m_window;

	public:
		RenderingContext(int screenWidth, int screenHeight);
		~RenderingContext();

		bool running();

		void update();

		int getWidth() const;
		int getHeight() const;
		float getAspectRatio() const;

		bool isKeyDown(int keyCode) const;
	};
}
