#include "CameraControllerSystem.h"

#include "Engine.h"
#include "systems/PhysicsSystem.h"
#include "settings.h"

#include <iostream>

void CameraControllerSystem::update()
{
    if (m_target == nullptr)
    {
        return;
    }
    auto camera = Engine::instance().get_camera();

    
    if (m_correct_for_gravity)
    {
        m_target_vel.y += Settings::GRAVITY_STRENGTH * static_cast<float>(Settings::UPDATE_TIME_MS) + 0.12f;
        m_target_vel.y = std::round(m_target_vel.y * 10.0f) / 10.0f;
        m_target_vel.y *= 0.3f;
    }
    

    const glm::vec2 target_pos = static_cast<glm::vec2>(*m_target) + preferred_position + m_target_vel * velocity_sensitivity;
    const glm::vec2 curr_pos = static_cast<glm::vec2>(m_transform_component);
    const glm::vec2 new_pos = curr_pos + speed * (target_pos - curr_pos);

    m_transform_component.x = new_pos.x;
    m_transform_component.y = new_pos.y;

    const float camera_z = camera->get_position().z;
    camera->set_position({ m_transform_component.x, m_transform_component.y, camera_z });

    m_target_vel = { 0.0f, 0.0f };
}