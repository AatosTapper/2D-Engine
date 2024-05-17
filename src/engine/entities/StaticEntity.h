#pragma once

#include "engine/Entity.h"
#include "engine/components/SpriteComponent.h"
#include "engine/components/AnimSpriteComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/ColliderComponent.h"
#include "engine/components/PhysicsComponent.h"

class StaticEntity : public Entity
{
public:
    StaticEntity() {}

    Transform2DComponent transform;
    BoxCollider2DComponent collider;
    PhysicsComponent physics;
    AnimSpriteComponent animation;

    void update_components() override;
    void on_attach() override;
};
