#include "CORE/Window.hpp"
#include "CORE/log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Engine {

    static bool isInitGLFW = false; 

	Window::Window(std::string tile, const unsigned int width, const unsigned int height)
        :m_data({std::move(tile), width, height})
	{
		int returnCode = init();
	}
	Window::~Window(){
		shotdown();
	}


    int Window::init() {
        LOG_INFO("Creating Window '{0}' size {1}x{2}", m_data.tile, m_data.width, m_data.height);

        if (!isInitGLFW) {
            if (!glfwInit()) {
                LOG_CRITICAL("Failed to intiliaze GLFW (for create window)");
                return -1;
            }
            isInitGLFW = true;
        }

        m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.tile.c_str(), nullptr, nullptr);
        if (m_window == nullptr)
        {
            LOG_CRITICAL("Failed to create Window '{0}'  size {1}x{2}", m_data.tile, m_data.width, m_data.height);
            glfwTerminate();
            return -2;
        }

          glfwMakeContextCurrent(m_window);


        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG_CRITICAL("Failed to intiliaze GLAD(for load OpenGL)");
            glfwTerminate();
            return -3;
        }


        glfwSetWindowUserPointer(m_window, &m_data);

        glfwSetWindowSizeCallback(m_window, 
            [](GLFWwindow* window, int width, int height) {
                WindowData& data = *static_cast<WindowData*>( glfwGetWindowUserPointer(window));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFN(event);
            });
        glfwSetCursorPosCallback(m_window,
            [](GLFWwindow* window, double curY, double curX) {
                WindowData& data = *static_cast<WindowData*> (glfwGetWindowUserPointer(window));
                EventMouseMoved event(curX, curY);
                data.eventCallbackFN(event);
            }
        );

        glfwSetWindowCloseCallback(m_window,
            [](GLFWwindow* window) {
                WindowData& data = *static_cast<WindowData*> (glfwGetWindowUserPointer(window));
                
                EventWindowClose event;
                data.eventCallbackFN(event);
            }
        );
        return 0;
	}

	void Window::shotdown() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
	}

	void Window::onUpdate() {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(m_window);
        glfwPollEvents();
	}
}