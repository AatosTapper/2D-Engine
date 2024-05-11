#include "PlayerGameObject.h"

#include "engine/Engine.h"
#include "engine/rendering/Renderer.h"

PlayerGameObject::PlayerGameObject()
{

}

void PlayerGameObject::update_components()
{
    glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    Renderer::instance().queue_sprite({ &sprite, full_transform });
}

void PlayerGameObject::on_attach()
{
    sprite.get_texture()->filter_nearest();
}

void PlayerGameObject::on_update()
{
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
}

void PlayerGameObject::on_destroy()
{

}
