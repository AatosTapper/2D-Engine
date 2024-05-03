#pragma once

#include <GLFW/glfw3.h> // TEMP

#include "../GameObject.h"
#include "../rendering/Sprite.h"
#include "../rendering/Renderer.h"
#include "../Window.h"

class ImageGameObject : public GameObject
{
public:
    Sprite sprite;

    void on_create(Scene *scene) override
    {
        (void)scene;
        sprite.add_texture("../res/textures/dirt.jpg");
    }

    void on_update(Scene *scene) override
    {
        sprite.position.z = (float)sin(glfwGetTime()) * 4;
        sprite.position.x = (float)cos(glfwGetTime() * 2) * 3;
        sprite.position.y = (float)cos(glfwGetTime() / 4) * 2;

        if (glfwGetKey(Window::get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
        {

            //scene->delete_game_object(get_id());
        }

        Renderer::queue_sprite(&sprite);
    }

    void on_destroy(Scene *scene) override
    {
        (void)scene;
        // nothing here now
    }
};

