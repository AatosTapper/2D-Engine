#pragma once

#include "../GameObject.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"

#include "../Scene.h"

class ImageGameObject : public GameObject
{
public:
    ImageGameObject(const char *texture_path);

    SpriteComponent sprite;
    Transform3DComponent transform;

    void on_attach() override;
    void on_update() override;
    void on_destroy() override;
};

