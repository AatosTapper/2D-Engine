#pragma once

#include "../GameObject.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../components/ColliderComponent.h"

class ImageGameObject : public GameObject
{
public:
    ImageGameObject(const char *texture_path);
    ImageGameObject();

    Transform3DComponent transform;
    SpriteComponent sprite;

    void update_components() override;
    void on_attach() override;
};

