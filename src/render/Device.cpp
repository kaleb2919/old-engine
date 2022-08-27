#include <string>
#include <iostream>
#include "Device.h"

Device::Device(int width, int height, std::string& title):
    width(width), height(height), title(title)
{
}

Device* Device::create(int width, int height, std::string& title)
{
    if (!is_initialized)
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return nullptr;
        }

        auto window = new Device(width, height, title);

        if (window->init())
        {
            is_initialized = true;
            return window;
        }
    }

    std::cerr << "Windows already initialized" << std::endl;
    return nullptr;
}

bool Device::init()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return window;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

bool Device::isRunning() {
    return !glfwWindowShouldClose(window);
}

void Device::clear()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Device::swap()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Device::close() {
    glfwTerminate();
}
