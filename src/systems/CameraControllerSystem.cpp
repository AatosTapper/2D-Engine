#include "CameraControllerSystem.h"

#include "Engine.h"
#include "systems/PhysicsSystem.h"
#include "settings.h"

#include <iostream>

CameraControllerSystem::CameraControllerSystem()
{
    m_physics_component.mass = 0.2f;
}

void CameraControllerSystem::update()
{
    if (m_target == nullptr)
    {
        return;
    }
    auto camera = Engine::instance().get_camera();

    // this is dodgy as fuck
    float camera_z = camera->get_position().z;
    camera->set_position({ m_transform_component.x, m_transform_component.y, camera_z - m_curr_z_offset });

    if (m_correct_for_gravity)
    {
        m_target_vel.y += Settings::GRAVITY_STRENGTH * static_cast<float>(Settings::UPDATE_TIME_MS) + 0.12f;
        m_target_vel.y = std::round(m_target_vel.y * 10.0f) / 10.0f;
        m_target_vel.y *= 0.3f;
    }

    const glm::vec2 target_pos = static_cast<glm::vec2>(m_transform_component) + preferred_position - m_target_vel * velocity_sensitivity;
    const glm::vec2 offset = static_cast<glm::vec2>(*m_target) - target_pos;

    const double speed_mult = speed * Settings::UPDATE_TIME_MS;
    const double damp_factor = std::pow(damp_per_sec, Settings::UPDATE_TIME_MS);

    m_physics_component.forces.x += static_cast<float>(std::pow(offset.x, 3) * speed_mult);
    m_physics_component.forces.y += static_cast<float>(std::pow(offset.y, 3) * speed_mult * 0.4);

    update_z_offset(offset);

    m_physics_component.velocity *= damp_factor;

    // dodgy af part 2
    camera_z = camera->get_position().z;
    camera->set_position({ m_transform_component.x, m_transform_component.y, camera_z + m_curr_z_offset });

    PhysicsSystem::instance().queue_entity({ NULL_ENTITY, m_physics_component, NULL_COLLIDER, m_transform_component });

    m_target_vel = { 0.0f, 0.0f };
}

void CameraControllerSystem::update_z_offset(const glm::vec2 &target_offset)
{
    if (glm::length(target_offset) > back_tresh)
    {
        if (m_curr_z_offset < max_z_dist)
        {
            m_z_vel += z_speed * Settings::UPDATE_TIME_MS;
            
            goto func_end;
        }
    }
    else if (m_curr_z_offset > 0.0f)
    {
        m_z_vel -= z_speed * Settings::UPDATE_TIME_MS;
    }

func_end:
    m_curr_z_offset += static_cast<float>(m_z_vel);
    m_z_vel *= std::pow(z_damp_per_sec, Settings::UPDATE_TIME_MS);
}
