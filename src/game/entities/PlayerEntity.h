#pragma once

#include "engine/Entity.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/ColliderComponent.h"
#include "engine/components/PhysicsComponent.h"
#include "engine/components/AnimSpriteComponent.h"
#include "engine/systems/TimerSystem.h"

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

