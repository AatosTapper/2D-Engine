#pragma once

#include "engine/rendering/Camera.h"
#include "engine/System.h"
#include "Ref.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/PhysicsComponent.h"

class CameraControllerSystem : public System
{
public:
    IMPL_VIRTUAL_SINGLETON_DISPATCHER(CameraControllerSystem, System)
    IMPL_NO_COPY(CameraControllerSystem)
    
    void update() override;

    void update_target(Ptr<Transform2DComponent> transform, const glm::vec2 &velocity = {0.0f, 0.0f}, bool correct_for_gravity = true);

    double speed = 30.0;               // this value is arbitary, "corresponds" to the force applied to the camera 
    double damp_per_sec = 0.06;        // cam velocity is multiplied by this amount within a one second

    double z_speed = 0.1;              // similar to "speed" but for z axis
    double z_damp_per_sec = 0.1;       // same as "damp_per_sec"
    float max_z_dist = 3.0f;           // how far can camera go back
    float back_tresh = 3.0f;           // how big offset from preferred position before moving back
    float velocity_sensitivity = 0.4f; // how much target velocity affects the preferred position

    glm::vec2 preferred_position = { 0.0f, 2.0f }; // where controller tries to position the target

private:
    CameraControllerSystem();

    void update_z_offset(const glm::vec2 &target_offset);

    Ptr<Transform2DComponent> m_target;
    glm::vec2 m_target_vel{};
    Transform2DComponent m_transform_component;
    PhysicsComponent m_physics_component;
    
    double m_z_vel = 0.0;
    float m_curr_z_offset = 0.0f;

    bool m_correct_for_gravity = true;
};

inline void CameraControllerSystem::update_target(Ptr<Transform2DComponent> transform, const glm::vec2 &velocity, bool correct_for_gravity) 
{
    m_target = transform;
    m_target_vel = velocity;
    m_correct_for_gravity = correct_for_gravity;
}