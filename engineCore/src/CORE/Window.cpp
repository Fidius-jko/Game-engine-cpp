#include "CORE/Window.hpp"
#include "CORE/log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h> 
#include <imgui/backends/imgui_impl_glfw.h> 


namespace Engine {

    static bool isInitGLFW = false; 

    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    const char* vertexSource =
        "#version 460\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos, 1.0f);\n"
        "   ourColor = aColor;\n"
        "}\n";
    const char* fragmentSource =
        "#version 460\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main() {\n"
        "   FragColor = vec4(ourColor, 1.0f);\n"
        "}\n";
    GLuint shaderProgram;
    GLuint VBO, VAO;


	Window::Window(std::string tile, const unsigned int width, const unsigned int height)
        :m_data({std::move(tile), width, height})
	{

		int returnCode = init();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
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


        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        GLuint VBO;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        return 0;
	}

	void Window::shotdown() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
	}

	void Window::onUpdate() {
        glClearColor(m_bangroundColor[0], m_bangroundColor[1], m_bangroundColor[2], m_bangroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(getWidth());
        io.DisplaySize.y = static_cast<float>(getHeight());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Banground window color");
        ImGui::ColorEdit4("Banground color", m_bangroundColor);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
        glfwPollEvents();
	}
}