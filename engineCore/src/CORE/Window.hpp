#pragma once

#include <string>

struct  GLFWwindow;

namespace Engine {
	class Window {
	public:
		Window(std::string tile, const unsigned int width, const unsigned int height);
		~Window();


		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void onUpdate();
		unsigned int getWidth() const { return m_width; }

		unsigned int getHeight() const { return m_height; }
	private:
		int init();
		void shotdown();

		std::string m_tile;
		GLFWwindow* m_window;
		unsigned int m_width;
		unsigned int m_height;

	};
}