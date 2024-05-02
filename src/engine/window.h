#pragma once

#include "../config.h"

// this class handles the application window and the graphics context

class Window
{
public:
    Window(int width, int height);
    ~Window();

    inline GLFWwindow *get_window() { return window; }
    inline bool is_open() { return !glfwWindowShouldClose(window); }
    void end_frame();

    glm::vec2 get_dimensions() const;
    inline float get_aspect_ratio() const { return (float)get_dimensions().x / get_dimensions().y; }

private:
    GLFWwindow *window;
};
