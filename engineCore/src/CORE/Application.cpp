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
        m_window->setEventCallback(
            [](Event& event)
            {
                LOG_INFO("Changed  window size to {0}x{1}", event.width, event.height);
            }
        );

        while (true) {
            m_window->onUpdate();
            onUpdate();
        }

        return 0;
    }

    void Application::onUpdate() {

    }
}