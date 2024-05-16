#pragma once

#include "engine/System.h"
#include "engine/components/ColliderComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/PhysicsComponent.h"
#include "singleton.h"
#include "Ref.h"
#include "settings.h"

#include <vector>
#include <tuple>

#define NULL_COLLIDER nullptr

class PhysicsSystem : public System
{
public:
    PhysicsSystem() {}
    ~PhysicsSystem() override {}
    IMPL_VIRTUAL_SINGLETON_DISPATCHER(PhysicsSystem, System)
    IMPL_NO_COPY(PhysicsSystem)

    // params: { physics component, box collider (optional), parent transform 2D }
    void queue_entity(std::tuple<Ref<PhysicsComponent>, Ptr<const BoxCollider2DComponent>, Ref<Transform2DComponent>> entity);

    // run simulation in multiple substeps for better collision accuracy etc
    void set_iterations(uint32_t new_iterations) { iterations = new_iterations; substep_delta_time = Settings::UPDATE_TIME_MS / static_cast<double>(iterations); }

    void update() override;

private:
    std::vector<std::tuple<Ref<PhysicsComponent>, Ptr<const BoxCollider2DComponent>, Ref<Transform2DComponent>>> entity_queue;
    uint32_t iterations = 8;
    double substep_delta_time = Settings::UPDATE_TIME_MS / static_cast<double>(iterations);

    void calc_collisions() const;
    glm::vec2 calc_mt_vec(
        const Ptr<const BoxCollider2DComponent> &col_1, 
        const Ptr<const BoxCollider2DComponent> &col_2, 
        const Ref<Transform2DComponent> pos_1, 
        const Ref<Transform2DComponent> pos_2) const;

    void integrate_forces(const Ref<PhysicsComponent> physics, const Ref<Transform2DComponent> transform, const double h) const;
};