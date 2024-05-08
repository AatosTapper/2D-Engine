#pragma once

#include "../GameObject.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../components/ColliderComponent.h"
#include "../systems/TimerSystem.h"

class PlayerGameObject : public GameObject
{
public:
    PlayerGameObject();
    
    Transform2DComponent transform;
    BoxCollider2DComponent collider;
    SpriteComponent sprite;

    TimerRef timer = nullptr;

    void update_components() override;
    void on_attach() override;
    void on_update() override;
    void on_destroy() override;

    void run_timer();
};

