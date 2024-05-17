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
        if (std::get<1>(entity_queue.at(i)) == nullptr) continue; // checking for collider

        for (uint32_t j = i + 1; j < entity_queue.size(); j++)
        {
            if (std::get<1>(entity_queue.at(j)) == nullptr) continue;

            calc_collision_impulses(entity_queue.at(i), entity_queue.at(j));            
        }
    }
}

glm::vec2 PhysicsSystem::calc_mt_vec(
    const Ptr<const BoxCollider2DComponent> &col_1, 
    const Ptr<const BoxCollider2DComponent> &col_2, 
    const Ref<Transform2DComponent> pos_1, 
    const Ref<Transform2DComponent> pos_2) const
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
    const float absLeft = std::abs(left);
    const float absRight = std::abs(right);
    const float absBottom = std::abs(bottom);
    const float absTop = std::abs(top);

    if (absLeft < absRight && absLeft < absBottom && absLeft < absTop)
    {
        output.x = right;
    }
    else if (absRight < absLeft && absRight < absBottom && absRight < absTop)
    {
        output.x = left;
    }
    else if (absBottom < absLeft && absBottom < absRight && absBottom < absTop)
    {
        output.y = top;
    }
    else
    {
        output.y = bottom;
    }

    return output;
}

void PhysicsSystem::calc_collision_impulses(const ComponentTuple &ent1, const ComponentTuple &ent2) const
{
    const auto [physics_1, collider_1, transform_1] = ent1;
    const auto [physics_2, collider_2, transform_2] = ent2;

    const glm::vec2 mtv = calc_mt_vec(collider_1, collider_2, transform_1, transform_2);

    if (mtv.x == 0.0f && mtv.y == 0.0f) return;
    
    const glm::vec2 relative_velocity = physics_1.get().velocity - physics_2.get().velocity;
    const glm::vec2 collision_normal = glm::normalize(mtv);
    const float relative_velocity_along_normal = glm::dot(relative_velocity, collision_normal);

    //if (relative_velocity_along_normal < 0.0f) return;

    const float e = std::min(physics_1.get().restitution, physics_2.get().restitution);
    const float impulse_magnitude = -(1.0f + e) * relative_velocity_along_normal;
    
    physics_1.get().forces += impulse_magnitude * collision_normal;
    physics_2.get().forces -= impulse_magnitude * collision_normal;

    // correcting positions
    const float percent = 0.005f;
    const float slop = 0.001f;
    const float inverse_mass_1 = 1.0f / physics_1.get().mass;
    const float inverse_mass_2 = 1.0f / physics_2.get().mass;
    const float correction_amount = std::max(glm::length(mtv) - slop, 0.0f) / (inverse_mass_1 + inverse_mass_2) * percent;
    const glm::vec2 correction = collision_normal * correction_amount;

    //std::cout << "X = " << collision_normal.x << "    Y = " << collision_normal.y << "\n";

    transform_1.get().x -= inverse_mass_1 * correction.x;
    transform_1.get().y -= inverse_mass_1 * correction.y;
    transform_2.get().x += inverse_mass_2 * correction.x;
    transform_2.get().y += inverse_mass_2 * correction.y;
}

void PhysicsSystem::integrate_forces(const Ref<PhysicsComponent> physics, const Ref<Transform2DComponent> transform, const double h) const
{
    const glm::vec2 acceleration = physics.get().forces / physics.get().mass;
    physics.get().velocity += acceleration;

    transform.get().x += static_cast<double>(physics.get().velocity.x) * h;
    transform.get().y += static_cast<double>(physics.get().velocity.y) * h;

    physics.get().forces = { 0.0f, 0.0f };
}