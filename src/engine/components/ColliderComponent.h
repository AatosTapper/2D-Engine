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
    glm::vec2 transform{0.0f};
    float radius{1.0f};
};