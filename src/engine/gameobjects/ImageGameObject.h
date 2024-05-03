#pragma once

#include "../GameObject.h"
#include "../rendering/Sprite.h"
#include "../rendering/Renderer.h"
#include "../Window.h"
#include "../components/TransformComponent.h"

#include "../Scene.h"

class ImageGameObject : public GameObject
{
public:
    Sprite sprite;
    Transform2DComponent transform;

    void on_create(Scene *scene) override;
    void on_update(Scene *scene) override;
    void on_destroy(Scene *scene) override;
};

