#pragma once

#include <GLFW/glfw3.h> // TEMP

#include "../GameObject.h"
#include "../rendering/Sprite.h"
#include "../rendering/Renderer.h"

class ImageGameObject : public GameObject
{
public:
    Sprite sprite;

    void on_create() override
    {
        sprite.add_texture("../res/textures/dirt.jpg");
    }

    void on_update() override
    {
        sprite.position.z = (float)sin(glfwGetTime()) * 4;
        sprite.position.x = (float)cos(glfwGetTime() * 3) * 3;
        sprite.position.y = (float)cos(glfwGetTime() / 2) * 2;

        Renderer::queue_sprite(&sprite);
    }

    void on_destroy() override
    {
        // nothing here now
    }
};

