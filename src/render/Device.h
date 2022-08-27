#ifndef OLD_ENGINE_DEVICE_H
#define OLD_ENGINE_DEVICE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Device {

    GLFWwindow* window = nullptr;

    int width;
    int height;

    std::string title;

    Device(int width, int height, std::string& title);

    static inline bool is_initialized = false;

    bool init();
public:
    Device & operator = (const Device&) = delete;
    Device(const Device&) = delete;

    static Device* create(int width, int height, std::string& title);


    bool isRunning();

    void clear();

    void swap();

    void close();
};


#endif //OLD_ENGINE_DEVICE_H
