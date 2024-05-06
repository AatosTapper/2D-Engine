#pragma once

#include "TransformComponent.h"

class BoxCollider2DComponent
{
public:
    Transform2DComponent transform;
};

// not implemented
class CircleCollider2DComponent
{
public:
    TransformPositionComponent transform;
    float radius{1.0f};
};