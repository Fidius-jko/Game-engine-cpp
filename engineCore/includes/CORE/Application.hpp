#pragma once
#include <memory>
#include "CORE/Event.hpp"

namespace Engine {
	class Application {
	public:
		Application();
		virtual ~Application();


		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		virtual int start(unsigned int windowWidth, unsigned int windowHeight, const char* tile);

		virtual void onUpdate();
	private:
		std::unique_ptr<class Window> m_window;

		EventDispatcher m_eventDispather;
		bool m_isCloseWindow = false;
	};
}