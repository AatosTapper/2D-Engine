#include "CameraControllerSystem.h"

#include "engine/Engine.h"
#include "engine/systems/PhysicsSystem.h"

#include <iostream>

CameraControllerSystem::CameraControllerSystem()
{
    m_physics_component.mass = 0.4f;
}

void CameraControllerSystem::update()
{
    if (m_target == nullptr)
    {
        return;
    }

    auto camera = Engine::instance().get_camera();
    // this is dodgy as fuck
    const auto camera_z = camera->get_position().z;
    camera->set_position({ m_transform_component.x, m_transform_component.y, camera_z });

    const glm::vec2 preferred_pos = static_cast<glm::vec2>(m_transform_component) + glm::vec2(0.0f, 1.0f);
    const glm::vec2 offset = static_cast<glm::vec2>(*m_target) - preferred_pos;

    // this is third order because I don't want to do sign magic rn
    m_transform_component.x += std::pow(offset.x, 3) * 0.2f * 0.01f;
    m_transform_component.y += std::pow(offset.y, 3) * 0.2f * 0.004f;

    //PhysicsSystem::instance().queue_entity({ nullptr, m_physics_component, NULL_COLLIDER, m_transform_component });
}
