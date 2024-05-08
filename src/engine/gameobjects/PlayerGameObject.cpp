#include "PlayerGameObject.h"

#include "../Engine.h"
#include "../rendering/Renderer.h"

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
}

void PlayerGameObject::on_attach()
{
    sprite.get_texture()->filter_nearest();
}

void PlayerGameObject::on_update()
{
    auto window = Engine::get_window()->get_glfw_window();
    
    run_timer();
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && timer == nullptr)
    {
        timer = TimerSystem::instance().set_timer(5);
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

void PlayerGameObject::run_timer()
{
    if (timer != nullptr)
    {
        if (timer->status == TIMER_STATUS::DONE)
        {
            std::cout << "Timer Done\n";
            // do other stuff here
        }
        if (timer->status == TIMER_STATUS::DELETE)
        {
            timer = nullptr;
        }
    }
}