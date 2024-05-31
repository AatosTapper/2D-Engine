#pragma once

#include "Entity.h"
#include "components/TransformComponent.h"
#include "components/ColliderComponent.h"
#include "components/PhysicsComponent.h"
#include "components/AnimSpriteComponent.h"
#include "systems/TimerSystem.h"

class PlayerEntity : public Entity
{
public:
    PlayerEntity();
    
    Transform2DComponent transform;
    PhysicsComponent physics;
    BoxCollider2DComponent collider;
    AnimSpriteComponent animation;

    void update_components() override;
    void on_attach() override;
    void on_update() override;
    void on_destroy() override;
};

