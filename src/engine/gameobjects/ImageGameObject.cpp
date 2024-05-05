#include "ImageGameObject.h"

#include "../Engine.h"

ImageGameObject::ImageGameObject(const char *texture_path)
{
    sprite.scale = glm::vec2(4.0f);
    sprite.add_texture(texture_path);
    sprite.texture->filter_nearest();
}

void ImageGameObject::on_attach()
{
    // nothing here now
}

void ImageGameObject::on_update()
{
    // THIS IS FOR TESTING
    
    transform.scale_x = 1.0f + (float)sin(glfwGetTime() * 1.5f) * 0.05f;
    transform.scale_y = 1.0f + (float)sin(glfwGetTime() * 1.5f) * -0.05f;

    if (glfwGetKey(Window::get_window(), GLFW_KEY_W) == GLFW_PRESS)
    {
        transform.y += 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_S) == GLFW_PRESS)
    {
        transform.y -= 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_A) == GLFW_PRESS)
    {
        transform.x -= 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_D) == GLFW_PRESS)
    {
        transform.x += 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        transform.rotation_rad_y -= 0.03f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        transform.rotation_rad_y += 0.03f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        transform.rotation_rad_x += 0.03f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        transform.rotation_rad_x -= 0.03f;
    }

    glm::mat4 full_transform = transform.get_matrix() * sprite.get_transform_matrix();
    Renderer::queue_sprite({ &sprite, full_transform });
}

void ImageGameObject::on_destroy()
{
    // nothing here now
}