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
    void update_target(Ptr<Transform2DComponent> transform) { m_target = transform; }

private:
    CameraControllerSystem();

    Ptr<Transform2DComponent> m_target;
    Transform2DComponent m_transform_component;
    PhysicsComponent m_physics_component;
};
