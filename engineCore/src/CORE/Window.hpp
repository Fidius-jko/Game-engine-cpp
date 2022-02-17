#pragma once

#include <string>
#include <functional>
#include "CORE/Event.hpp"

struct  GLFWwindow;

namespace Engine {
	class Window {
	public:
		using EventCallbackFN = std::function<void(BaseEvent&)>;

		Window(std::string tile, const unsigned int width, const unsigned int height);
		~Window();


		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void onUpdate();
		unsigned int getWidth() const { return m_data.width; }

		unsigned int getHeight() const { return m_data.height; }

		void setEventCallback(EventCallbackFN callback) {
			m_data.eventCallbackFN = callback;
		}
	private:
		struct WindowData
		{
			std::string tile;
			unsigned int width;
			unsigned int height;
			EventCallbackFN eventCallbackFN;
		};

		int init();
		void shotdown();

		GLFWwindow* m_window;
		WindowData m_data;
		float m_bangroundColor[4] = {1.0f, 0.0f, 0.0f, 0.0f};
	};
}