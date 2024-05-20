#include "PhysicsSystem.h"

#include <iostream>

void PhysicsSystem::queue_entity(ComponentTuple entity)
{
    entity_queue.push_back(entity);
}

void PhysicsSystem::update()
{
    // initial force calculations don't benefit from substeps 
    for (const auto &entity : entity_queue)
    {
        integrate_forces(std::get<0>(entity), std::get<2>(entity), Settings::UPDATE_TIME_MS / 2.0);
    }

    if (entity_queue.size() >= 2)
    {
        // solve collisions with multiple iterations
        for (uint32_t i = 0; i < iterations; i++)
        {
            calc_collisions(); 
            for (const auto &entity : entity_queue)
            {
                integrate_forces(std::get<0>(entity), std::get<2>(entity), substep_delta_time / 2.0);
            }
        }
    }

    entity_queue.clear();
}

void PhysicsSystem::calc_collisions() const
{
    for (uint32_t i = 0; i < entity_queue.size() - 1; i++)
    {
        if (std::get<1>(entity_queue.at(i)) == NULL_COLLIDER) continue; // checking for collider

        for (uint32_t j = i + 1; j < entity_queue.size(); j++)
        {
            if (std::get<1>(entity_queue.at(j)) == NULL_COLLIDER) continue;

            resolve_collision(entity_queue.at(i), entity_queue.at(j));            
        }
    }
}

glm::vec2 PhysicsSystem::calc_mt_vec(const Ptr<const BoxCollider2DComponent> &col_1, const Ptr<const BoxCollider2DComponent> &col_2, const Ref<Transform2DComponent> pos_1, const Ref<Transform2DComponent> pos_2) const
{
    glm::vec2 output(0.0f);

    const float a_l = static_cast<float>(pos_1.get().x) - (col_1.get()->width);
    const float a_r = static_cast<float>(pos_1.get().x) + (col_1.get()->width);
    const float b_l = static_cast<float>(pos_2.get().x) - (col_2.get()->width);
    const float b_r = static_cast<float>(pos_2.get().x) + (col_2.get()->width);

    const float a_t = static_cast<float>(pos_1.get().y) + (col_1.get()->height);
    const float a_b = static_cast<float>(pos_1.get().y) - (col_1.get()->height);
    const float b_t = static_cast<float>(pos_2.get().y) + (col_2.get()->height);
    const float b_b = static_cast<float>(pos_2.get().y) - (col_2.get()->height);

    const float left = b_l - a_r;
    const float right = b_r - a_l;
    const float bottom = b_b - a_t;
    const float top = b_t - a_b;

    // Check if the AABBs are not overlapping
    if (left > 0.0f || right < 0.0f || bottom > 0.0f || top < 0.0f) 
    {
        return output;
    }

    // Calculate the MTV for overlapping AABBs
    const float abs_left = std::abs(left);
    const float abs_right = std::abs(right);
    const float abs_bottom = std::abs(bottom);
    const float abs_top = std::abs(top);

    if (abs_left < abs_right && abs_left < abs_bottom && abs_left < abs_top)
    {
        output.x = right;
    }
    else if (abs_right < abs_left && abs_right < abs_bottom && abs_right < abs_top)
    {
        output.x = left;
    }
    else if (abs_bottom < abs_left && abs_bottom < abs_right && abs_bottom < abs_top)
    {
        output.y = top;
    }
    else
    {
        output.y = bottom;
    }

    return output;
}

void PhysicsSystem::resolve_collision(const ComponentTuple &ent1, const ComponentTuple &ent2) const
{
    const auto [physics_1, collider_1, transform_1] = ent1;
    const auto [physics_2, collider_2, transform_2] = ent2;

    const glm::vec2 mtv = calc_mt_vec(collider_1, collider_2, transform_1, transform_2);

    if (mtv.x == 0.0f && mtv.y == 0.0f) return;
    
    const glm::vec2 relative_velocity = physics_1.get().velocity - physics_2.get().velocity;
    const glm::vec2 collision_normal = glm::normalize(mtv);
    const float relative_velocity_along_normal = glm::dot(relative_velocity, collision_normal);

    if (relative_velocity_along_normal < 0.0f) return;

    const float e = std::min(physics_1.get().restitution, physics_2.get().restitution);
    const float impulse_magnitude = -(1.0f + e) * relative_velocity_along_normal;
    
    physics_1.get().forces += impulse_magnitude * collision_normal;
    physics_2.get().forces -= impulse_magnitude * collision_normal;

    // correcting positions
    const float percent = std::max(0.4f / iterations, 0.01f);
    const float slop = 0.04f;
    const float penetration_depth = std::max(std::max(std::abs(mtv.x), std::abs(mtv.y)) - slop, 0.0f);
    const float correction_amount = penetration_depth * percent * 0.1f;

    const glm::vec2 correction = collision_normal * correction_amount;

    const float mass_ratio_1 = physics_2.get().mass / (physics_1.get().mass + physics_2.get().mass);
    const float mass_ratio_2 = physics_1.get().mass / (physics_1.get().mass + physics_2.get().mass);

    transform_1.get().x -= correction.x * mass_ratio_1;
    transform_1.get().y -= correction.y * mass_ratio_1;
    transform_2.get().x += correction.x * mass_ratio_2;
    transform_2.get().y += correction.y * mass_ratio_2;
}

void PhysicsSystem::integrate_forces(const Ref<PhysicsComponent> physics, const Ref<Transform2DComponent> transform, const double h) const
{
#ifdef PHYSICS_SOLVER_EULER

    const glm::vec2 acceleration = physics.get().forces / physics.get().mass;
    physics.get().velocity += acceleration;

    transform.get().x += static_cast<double>(physics.get().velocity.x) * h;
    transform.get().y += static_cast<double>(physics.get().velocity.y) * h;

    physics.get().forces = { 0.0f, 0.0f };

#elif defined(PHYSICS_SOLVER_RK4)
    
    static_assert(false, "PHYSICS_SOLVER_RK4");

#endif
}