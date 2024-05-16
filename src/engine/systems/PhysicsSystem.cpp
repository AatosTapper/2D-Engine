#include "PhysicsSystem.h"

#include <functional>

void PhysicsSystem::queue_entity(std::tuple<Ref<PhysicsComponent>, Ptr<const BoxCollider2DComponent>, Ref<Transform2DComponent>> entity)
{
    entity_queue.push_back(entity);
}

void PhysicsSystem::update()
{
    // trying to optimize branch prediction
    std::function<void()> solve_collisions = [this]
    {
        calc_collisions(); 
        for (const auto &entity : entity_queue)
        {
            integrate_forces(std::get<0>(entity), std::get<2>(entity), substep_delta_time);
        }
    };
    if (entity_queue.size() < 2) { solve_collisions = []{}; }

    // initial force calculations don't benefit from substeps 
    for (const auto &entity : entity_queue)
    {
        integrate_forces(std::get<0>(entity), std::get<2>(entity), Settings::UPDATE_TIME_MS);
    }
    // solve collisions with multiple iterations
    for (uint32_t i = 0; i < iterations; i++)
    {
        solve_collisions();
    }
    entity_queue.clear();
}

void PhysicsSystem::calc_collisions() const
{
    for (const auto &entity : entity_queue)
    {
        auto [physics, collider, transform] = entity;
        if (collider == nullptr)
        {
            continue;
        }

        // TODO ADD ANOTHER LOOP
    }
}

glm::vec2 PhysicsSystem::calc_mt_vec(
    const Ptr<const BoxCollider2DComponent> &col_1, 
    const Ptr<const BoxCollider2DComponent> &col_2, 
    const Ref<Transform2DComponent> pos_1, 
    const Ref<Transform2DComponent> pos_2) const
{
    return glm::vec2(0.0f);
    /*
    this is saved here so i don't need to write it again

    void solve_AABB(BoxCollider2DComponent *box1, BoxCollider2DComponent *box2)
    {
        //   y1
        // x1  x2
        //   y2

        double b1x1 = box1->transform.x - ( box1->transform.scale_x * box1->transform.scale );
        double b1x2 = box1->transform.x + ( box1->transform.scale_x * box1->transform.scale );
        double b2x1 = box2->transform.x - ( box2->transform.scale_x * box2->transform.scale );
        double b2x2 = box2->transform.x + ( box2->transform.scale_x * box2->transform.scale );

        double b1y1 = box1->transform.y + ( box1->transform.scale_y * box1->transform.scale );
        double b1y2 = box1->transform.y - ( box1->transform.scale_y * box1->transform.scale );
        double b2y1 = box2->transform.y + ( box2->transform.scale_y * box2->transform.scale );
        double b2y2 = box2->transform.y - ( box2->transform.scale_y * box2->transform.scale );

        if (b1x2 > b2x1 && b2x2 > b1x1 && b1y1 > b2y2 && b1y2 < b2y1)
        {
            // collision
        }
    }

    */
}

void PhysicsSystem::integrate_forces(const Ref<PhysicsComponent> physics, const Ref<Transform2DComponent> transform, const double h) const
{
    // TODO: use Runge Kutta 4 integration to calculate the new velocity and apply it to the position
    
    // currently just euler's method

    const float inverse_mass = 1.0f / physics.get().mass;

    const glm::vec2 acceleration = physics.get().get_forces() * inverse_mass;
    physics.get().velocity += acceleration;

    transform.get().x += static_cast<double>(physics.get().velocity.x) * h;
    transform.get().y += static_cast<double>(physics.get().velocity.y) * h;

    physics.get().get_forces() = { 0.0f, 0.0f };
}