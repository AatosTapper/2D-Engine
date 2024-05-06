#include "CollisionSystem.h"

#include <iostream>
#include <cassert>

System &CollisionSystem::get_base_instance()
{
    return dynamic_cast<System&>(instance());
}

CollisionSystem &CollisionSystem::instance()
{
    static CollisionSystem instance;
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
            auto box1 = box_queue[i];
            auto box2 = box_queue[j];

            // not good here

            box1.first->transform.x += box1.second.x;
            box1.first->transform.y += box1.second.y;
            box2.first->transform.x += box2.second.x;
            box2.first->transform.y += box2.second.y;

            solve_AABB(box1.first, box2.first);

            box1.first->transform.x -= box1.second.x;
            box1.first->transform.y -= box1.second.y;
            box2.first->transform.x -= box2.second.x;
            box2.first->transform.y -= box2.second.y;
        }
    }

    box_queue.clear();
}

void CollisionSystem::queue_collider(std::pair<BoxCollider2DComponent*, glm::vec2> box)
{
    assert(std::get<0>(box) && "Cannot queue a collider that's value is null");

    box_queue.push_back(box);
}

void CollisionSystem::solve_AABB(BoxCollider2DComponent *box1, BoxCollider2DComponent *box2) const
{
    //   y1
    // x1  x2
    //   y2

    double b1x1 = box1->transform.x - ( box1->transform.scale_x * box1->transform.scale );
    double b1x2 = box1->transform.x + ( box1->transform.scale_x * box1->transform.scale );
    double b2x1 = box2->transform.x - ( box2->transform.scale_x * box2->transform.scale );
    double b2x2 = box2->transform.x + ( box2->transform.scale_x * box2->transform.scale );

    double b1y1 = box1->transform.y + ( box1->transform.scale_y * box1->transform.scale );
    double b1y2 = box1->transform.y - ( box1->transform.scale_y * box1->transform.scale );
    double b2y1 = box2->transform.y + ( box2->transform.scale_y * box2->transform.scale );
    double b2y2 = box2->transform.y - ( box2->transform.scale_y * box2->transform.scale );

    if (b1x2 > b2x1 && b2x2 > b1x1 && b1y1 > b2y2 && b1y2 < b2y1)
    {
        // collision
    }
}