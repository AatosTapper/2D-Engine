#pragma once

#include "engine/System.h"
#include "engine/components/ColliderComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/PhysicsComponent.h"
#include "singleton.h"
#include "Ref.h"
#include "settings.h"
#include "engine/Entity.h"

#include <vector>
#include <tuple>

#define NULL_COLLIDER nullptr

using ComponentTuple = std::tuple<Ptr<Entity>, Ref<PhysicsComponent>, Ptr<const BoxCollider2DComponent>, Ref<Transform2DComponent>>;

class PhysicsSystem : public System
{
public:
    PhysicsSystem() {}
    ~PhysicsSystem() override {}
    IMPL_VIRTUAL_SINGLETON_DISPATCHER(PhysicsSystem, System)
    IMPL_NO_COPY(PhysicsSystem)

    // params: { &entity, physics component, &box collider (optional), parent transform 2D }
    void queue_entity(ComponentTuple entity);

    // run simulation in multiple substeps for better collision accuracy etc
    void set_iterations(uint32_t new_iterations) { m_iterations = new_iterations; m_substep_delta_time = Settings::UPDATE_TIME_MS / static_cast<double>(m_iterations); }

    void update() override;

private:
    std::vector<ComponentTuple> m_entity_queue;
    uint32_t m_iterations = Settings::INITIAL_PHYSICS_ITERATIONS;
    double m_substep_delta_time = Settings::UPDATE_TIME_MS / static_cast<double>(m_iterations);

    void calc_collisions() const;
    glm::vec2 calc_mt_vec(const Ptr<const BoxCollider2DComponent> &col_1, const Ptr<const BoxCollider2DComponent> &col_2, const Ref<Transform2DComponent> pos_1, const Ref<Transform2DComponent> pos_2) const;
    void resolve_collision(const ComponentTuple &ent1, const ComponentTuple &ent2) const;
    void integrate_forces(const Ref<PhysicsComponent> physics, const Ref<Transform2DComponent> transform, double h) const;
    void add_gravity(const Ref<PhysicsComponent> physics) const;
};