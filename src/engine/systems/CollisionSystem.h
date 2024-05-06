#pragma once

#include "../System.h"
#include "../components/ColliderComponent.h"
#include "../components/TransformComponent.h"

#include "../../config.h"

#include <tuple>
#include <vector>



// this system will be deleted when physics system comes



class CollisionSystem : System
{
public:
    void update() override;
    // 1. box collider, 2. parent position
    void queue_collider(std::pair<BoxCollider2DComponent*, TransformPositionComponent> box);

    static System *get_base_instance();
    static CollisionSystem *get_instance();

private:
    static CollisionSystem *instance;

    std::vector<BoxCollider2DComponent*> box_queue;

    void solve_AABB(BoxCollider2DComponent *box1, BoxCollider2DComponent *box2) const;
};