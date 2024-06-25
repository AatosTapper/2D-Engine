#pragma once

#include "config.h"
#include "settings.h"
#include "Ref.h"
#include "Flags.h"

class PhysicsComponent
{
public:
    glm::vec2 velocity{0.0f};   // m/s
    glm::vec2 forces{0.0f};     // N
    glm::vec2 temp_acc{0.0f};   // m^2/s (used for physics system internal calculations)
    float mass = 1.0f;          // kg
    float restitution = 1.3f;   // range 1.0f to 2.0f
    float friction = 0.6f;      // range 0.0f to 1.0f

    // flags
    constexpr void set_flags(PhysicsFlags flag) { m_flags |= flag; }
    constexpr void remove_flags(PhysicsFlags flag) { m_flags &= ~flag; }
    [[nodiscard]] constexpr bool has_flags(PhysicsFlags flag) const { return 0 != (m_flags & flag); }

private:
    Bitflag m_flags = 0u;
};