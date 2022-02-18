#include <iostream>
#include "CORE/Application.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CORE/log.hpp"
#include "CORE/Window.hpp"

namespace Engine {
    Application::Application() {
        LOG_INFO("Starting Application");
    }
    Application::~Application() {

        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int windowWidth, unsigned int windowHeight, const char* tile) {
        m_window = std::make_unique<Window>(tile, windowWidth, windowHeight);
        m_eventDispather.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                //LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            });
        m_eventDispather.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event) {
                LOG_INFO("[Resized] Changed size to {0}x{1}", event.width, event.height);
            }
        );
        m_eventDispather.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event) {
                LOG_INFO("[WindowClose]");
                m_isCloseWindow = true;
            }
        );

        m_window->setEventCallback(
            [&](BaseEvent& event)
            {
                m_eventDispather.dispatch(event);
            }
        );

        while (!m_isCloseWindow) {
            m_window->onUpdate();
            onUpdate();
        }

        m_window = nullptr;

        return 0;
    }

    void Application::onUpdate() {

    }
}