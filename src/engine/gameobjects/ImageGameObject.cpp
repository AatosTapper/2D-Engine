#include "ImageGameObject.h"

#include "../Engine.h"
#include "../rendering/Renderer.h"

ImageGameObject::ImageGameObject(const char *texture_path)
{
    sprite.transform.scale = 4.0f;
    sprite.add_texture(texture_path);
    sprite.texture->filter_nearest();
}

void ImageGameObject::on_attach()
{
    // nothing here now
}

void ImageGameObject::update_components()
{
    glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    Renderer::instance().queue_sprite({ &sprite, full_transform });
}

void ImageGameObject::on_update()
{
    // THIS IS FOR TESTING
    
    transform.scale_x = 1.0f + (float)sin(glfwGetTime() * 1.5f) * 0.05f;
    transform.scale_y = 1.0f + (float)sin(glfwGetTime() * 1.5f) * -0.05f;

    auto window = Engine::get_window()->get_glfw_window();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        transform.y += 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        transform.y -= 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        transform.x -= 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        transform.x += 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        transform.rotation_rad_y -= 0.03f;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        transform.rotation_rad_y += 0.03f;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        transform.rotation_rad_x += 0.03f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        transform.rotation_rad_x -= 0.03f;
    }
}

void ImageGameObject::on_destroy()
{
    // nothing here now
}