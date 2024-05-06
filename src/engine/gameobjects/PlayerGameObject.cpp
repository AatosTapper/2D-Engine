#include "PlayerGameObject.h"

#include "../Engine.h"
#include "../rendering/Renderer.h"
#include "../systems/CollisionSystem.h"

PlayerGameObject::PlayerGameObject()
{
    //sprite.add_texture("../res/textures/rock.png");

    transform.scale_x = 2.0f;
    collider.transform.scale_x = 2.0f;
}

void PlayerGameObject::update_components()
{
    glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    Renderer::instance().queue_sprite({ &sprite, full_transform });
    CollisionSystem::instance().queue_collider({ &collider, static_cast<glm::vec2>(transform) });
}

void PlayerGameObject::on_attach()
{
    sprite.texture->filter_nearest();
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