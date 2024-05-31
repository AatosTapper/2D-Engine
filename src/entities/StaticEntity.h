#pragma once

#include "Entity.h"
#include "components/SpriteComponent.h"
#include "components/AnimSpriteComponent.h"
#include "components/TransformComponent.h"
#include "components/ColliderComponent.h"
#include "components/PhysicsComponent.h"

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
