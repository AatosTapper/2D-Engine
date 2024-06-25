#pragma once

#include "rendering/Camera.h"
#include "System.h"
#include "Ref.h"
#include "components/TransformComponent.h"
#include "components/PhysicsComponent.h"

class CameraControllerSystem : public System
{
public:
    IMPL_VIRTUAL_SINGLETON_DISPATCHER(CameraControllerSystem, System)
    IMPL_NO_COPY(CameraControllerSystem)
    
    void update() override;

    void update_target(Ptr<Transform2DComponent> transform, const glm::vec2 &velocity = {0.0f, 0.0f}, bool correct_for_gravity = true);

    float speed = 0.03f;                             // timestep of the lerp
    float velocity_sensitivity = 0.5f;              // how much target velocity affects the preferred position
    glm::vec2 preferred_position = { 0.0f, -1.0f }; // where controller tries to position the target

private:
    CameraControllerSystem() {}

    Ptr<Transform2DComponent> m_target;
    glm::vec2 m_target_vel{};
    Transform2DComponent m_transform_component;

    bool m_correct_for_gravity = true;
};

inline void CameraControllerSystem::update_target(Ptr<Transform2DComponent> transform, const glm::vec2 &velocity, bool correct_for_gravity) 
{
    m_target = transform;
    m_target_vel = velocity;
    m_correct_for_gravity = correct_for_gravity;
}