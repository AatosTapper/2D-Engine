#include "Window.h"

#include "engine/rendering/Renderer.h"

#include <iostream>
#include <cassert>
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void check_for_key_close(GLFWwindow *window);

static bool window_resized = false;

Window::Window(int width, int height)
{
    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW\n";
        assert(false);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing (MSAA)

    // some apple shit
#ifdef __APPLE__
    std::cout << "Apple compatability on\n";
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "2D-Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        assert(false);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        assert(false);
    }

    int fb_width = 0, fb_height = 0;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::end_frame()
{   
    // closes the window if user presses ESC
    check_for_key_close(window);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
}

glm::vec2 Window::get_dimensions() const
{
    int fb_width = 0, fb_height = 0;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);

    return glm::vec2((float)fb_width, (float)fb_height);
}

bool Window::did_resize() const
{
    return window_resized;
}

void Window::reset_resize_flag() const
{
    window_resized = false;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window; // this silences the warning about "unused parameter"
    glViewport(0, 0, width, height);
    window_resized = true;
}

static void check_for_key_close(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
