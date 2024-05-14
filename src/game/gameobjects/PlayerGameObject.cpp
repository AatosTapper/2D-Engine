#include "PlayerGameObject.h"

#include "engine/Engine.h"
#include "engine/rendering/Renderer.h"

PlayerGameObject::PlayerGameObject()
{
    set_flags(PLAYER);
    animation.set_fps(60); // optional because 60 is the default but this allows anything
}

void PlayerGameObject::update_components()
{
    //glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    //Renderer::instance().queue_sprite({ &sprite, full_transform });
    animation.update(transform.get_matrix());
}

void PlayerGameObject::on_attach()
{
    sprite.get_texture()->filter_nearest();

    animation.push_folder_as_frames("../res/animations/test_anim");
}

void PlayerGameObject::on_update()
{
    auto window = Engine::instance().get_window()->get_glfw_window();

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        animation.play(AnimSpriteComponent::PlaybackType::ONE_SHOT);
    }

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
