#pragma once

#include "engine/GameObject.h"
#include "engine/components/SpriteComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/ColliderComponent.h"
#include "engine/systems/TimerSystem.h"

class PlayerGameObject : public GameObject
{
public:
    PlayerGameObject();
    
    Transform2DComponent transform;
    BoxCollider2DComponent collider;
    SpriteComponent sprite;

    TimerRef timer = nullptr; // this is for testing the timer system

    void update_components() override;
    void on_attach() override;
    void on_update() override;
    void on_destroy() override;

    void run_timer();
};

