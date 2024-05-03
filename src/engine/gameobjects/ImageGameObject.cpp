#include "ImageGameObject.h"

void ImageGameObject::on_create(Scene *scene)
{
    (void)scene;
    sprite.add_texture("../res/textures/dirt.jpg");
}

void ImageGameObject::on_update(Scene *scene)
{
    (void)scene;
    // THIS IS FOR TESTING, PLAYER WON'T BE ABLE TO CONTROL THIS TRANSFORM

    sprite.position.z = (float)sin(glfwGetTime() / 2) * 3.0f;
    sprite.position.x = (float)cos(glfwGetTime() * 2) * 0.3f;
    sprite.position.y = (float)cos(glfwGetTime()    ) * 0.2f;

    if (glfwGetKey(Window::get_window(), GLFW_KEY_W) == GLFW_PRESS)
    {
        transform.position.y += 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_S) == GLFW_PRESS)
    {
        transform.position.y -= 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_A) == GLFW_PRESS)
    {
        transform.position.x -= 0.1f;
    }

    if (glfwGetKey(Window::get_window(), GLFW_KEY_D) == GLFW_PRESS)
    {
        transform.position.x += 0.1f;
    }

    glm::mat4 full_transform = transform.get_matrix() * sprite.get_transform_matrix();
    Renderer::queue_sprite({ &sprite, full_transform });
}

void ImageGameObject::on_destroy(Scene *scene)
{
    (void)scene;
    // nothing here now
}