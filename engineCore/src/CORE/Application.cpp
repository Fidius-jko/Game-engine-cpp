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

        while (true) {
            m_window->onUpdate();
            onUpdate();
        }
    }

    void Application::onUpdate() {

    }
}