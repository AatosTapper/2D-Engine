#pragma once

#include "config.h"
#include "settings.h"
#include "Ref.h"

class PhysicsComponent
{
public:
    glm::vec2 velocity{0.0};   // m/s
    float mass = 1.0f;          // kg
    float restitution = 1.0f;   // range 1.0f to 2.0f

    void add_force_x(float force) { forces.x += force * static_cast<float>(Settings::UPDATE_TIME_MS); }
    void add_force_y(float force) { forces.y += force * static_cast<float>(Settings::UPDATE_TIME_MS); }
    void add_force(glm::vec2 force) { forces += force * static_cast<float>(Settings::UPDATE_TIME_MS); }
    [[nodiscard]] glm::vec2 &get_forces() { return forces; }

private:
    glm::vec2 forces{0.0f};     // N
};