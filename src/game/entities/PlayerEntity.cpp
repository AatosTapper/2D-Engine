#include "PlayerEntity.h"

#include "settings.h"
#include "engine/Engine.h"
#include "engine/rendering/Renderer.h"
#include "engine/systems/PhysicsSystem.h"

PlayerEntity::PlayerEntity()
{
    set_flags(PLAYER);
    animation.set_fps(60); // optional because 60 is the default but this allows anything
}

void PlayerEntity::update_components()
{
    //glm::mat4 full_transform = transform.get_matrix() * sprite.transform.get_matrix();
    //Renderer::instance().queue_sprite({ &sprite, full_transform });
    animation.update(transform.get_matrix());
    PhysicsSystem::instance().queue_entity({ physics, &collider, transform });

    physics.mass = 10.0f;
}

void PlayerEntity::on_attach()
{
    animation.push_folder_as_frames("../res/animations/test_anim");
}

void PlayerEntity::on_update()
{
    auto window = Engine::instance().get_window()->get_glfw_window();

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        animation.play(AnimSpriteComponent::PlaybackType::ONE_SHOT);
    }
    constexpr float speed = 3.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        physics.forces.y += speed;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        physics.forces.y -= speed;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        physics.forces.x -= speed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        physics.forces.x += speed;
    }
}

void PlayerEntity::on_destroy()
{

}
