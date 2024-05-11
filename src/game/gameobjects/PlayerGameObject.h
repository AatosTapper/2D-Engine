#pragma once

#include "engine/GameObject.h"
#include "engine/components/SpriteComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/ColliderComponent.h"
#include "engine/components/AnimSpriteComponent.h"
#include "engine/systems/TimerSystem.h"

class PlayerGameObject : public GameObject
{
public:
    PlayerGameObject();
    
    Transform2DComponent transform;
    BoxCollider2DComponent collider;
    SpriteComponent sprite;
    AnimSpriteComponent animation;

    void update_components() override;
    void on_attach() override;
    void on_update() override;
    void on_destroy() override;
};

