#pragma once

#include "../GameObject.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../components/ColliderComponent.h"

class PlayerGameObject : public GameObject
{
public:
    PlayerGameObject();
    
    Transform2DComponent transform;
    BoxCollider2DComponent collider;
    SpriteComponent sprite;

    void update_components() override;
    void on_attach() override;
    void on_update() override;
    void on_destroy() override;
};

