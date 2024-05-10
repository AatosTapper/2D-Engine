#pragma once

#include "config.h"

// this class handles the application window and the graphics context

class Window
{
public:
    Window(int width, int height);
    ~Window();

    GLFWwindow *get_glfw_window() const { return window; }
    bool is_open() const { return !glfwWindowShouldClose(window); }
    void end_frame();

    [[nodiscard]] bool did_resize() const;
    [[nodiscard]] glm::vec2 get_dimensions() const;
    [[nodiscard]] int get_width() const { return static_cast<int>(get_dimensions().x); }
    [[nodiscard]] int get_height() const { return static_cast<int>(get_dimensions().y); }
    [[nodiscard]] float get_aspect_ratio() const { return (float)get_dimensions().x / get_dimensions().y; }

    void reset_resize_flag() const;

private:
    GLFWwindow *window;
};
