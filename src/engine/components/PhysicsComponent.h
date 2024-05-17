#pragma once

#include "config.h"
#include "settings.h"
#include "Ref.h"

class PhysicsComponent
{
public:
    glm::vec2 velocity {0.0};   // m/s
    glm::vec2 forces {0.0f};
    float mass {1.0f};          // kg
    float restitution {1.0f};   // range 1.0f to 2.0f
};