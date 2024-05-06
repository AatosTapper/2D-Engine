#include "CollisionSystem.h"

#include <iostream>
#include <cassert>

CollisionSystem *CollisionSystem::instance = nullptr;

System *CollisionSystem::get_base_instance()
{
    if (instance == nullptr)
    {
        instance = new CollisionSystem();
    }
    return dynamic_cast<System*>(instance);
}

CollisionSystem *CollisionSystem::get_instance()
{
    if (instance == nullptr)
    {
        instance = new CollisionSystem();
    }
    return instance;
}

void CollisionSystem::update()
{
    if (box_queue.size() < 2)
    {
        box_queue.clear();
        return;
    }

    for (uint32_t i = 0; i < box_queue.size() - 1; i++)
    {
        for (uint32_t j = i + 1; j < box_queue.size(); j++)
        {
            solve_AABB(box_queue[i], box_queue[j]);
        }
    }

    box_queue.clear();
}

void CollisionSystem::queue_collider(std::pair<BoxCollider2DComponent*, TransformPositionComponent> box)
{
    auto collider = std::get<0>(box);
    auto transform = std::get<1>(box);

    assert(collider && "Cannot queue a collider that's value is null");

    collider->transform.x += transform.x;
    collider->transform.y += transform.y;

    box_queue.push_back(collider);
}

void CollisionSystem::solve_AABB(BoxCollider2DComponent *box1, BoxCollider2DComponent *box2) const
{
    //   y1
    // x1  x2
    //   y2

    // TODO: check radius before calculating AABB

    double b1x1 = box1->transform.x - ( box1->transform.scale_x * box1->transform.scale );
    double b1x2 = box1->transform.x + ( box1->transform.scale_x * box1->transform.scale );
    double b2x1 = box2->transform.x - ( box2->transform.scale_x * box2->transform.scale );
    double b2x2 = box2->transform.x + ( box2->transform.scale_x * box2->transform.scale );

    double b1y1 = box1->transform.y + ( box1->transform.scale_y * box1->transform.scale );
    double b1y2 = box1->transform.y - ( box1->transform.scale_y * box1->transform.scale );
    double b2y1 = box2->transform.y + ( box2->transform.scale_y * box2->transform.scale );
    double b2y2 = box2->transform.y - ( box2->transform.scale_y * box2->transform.scale );

    if (b1x2 > b2x1 || b1x1 < b2x2)
    {
        if (b1y2 < b2y1 || b1y1 > b2y2)
        {
            std::cout << "Collision!\n";
        }
    }
}