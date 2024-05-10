#pragma once

#include "engine/components/TransformComponent.h"

class BoxCollider2DComponent
{
public:
    Transform2DComponent transform;
};

// not implemented
class CircleCollider2DComponent
{
public:
    glm::vec2 transform{0.0f};
    float radius{1.0f};
};




/*

this is saved here so i don't need to write it again

void solve_AABB(BoxCollider2DComponent *box1, BoxCollider2DComponent *box2)
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

*/