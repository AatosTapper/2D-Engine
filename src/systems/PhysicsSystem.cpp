#include "PhysicsSystem.h"

#include "eng_util.h"

#include <iostream>

void PhysicsSystem::queue_entity(ComponentTuple entity)
{
    m_entity_queue.push_back(entity);
}

void PhysicsSystem::update()
{    
    // initial force calculations don't benefit from substeps 
    for (const auto &entity : m_entity_queue)
    {
        if (std::get<1>(entity).get().has_flags(PhysicsFlags::HAS_GRAVITY))
        {
            add_gravity(std::get<1>(entity));
        }
        integrate_forces(std::get<1>(entity), std::get<3>(entity), Settings::UPDATE_TIME_MS / 2.0);

        if (std::get<0>(entity) != NULL_ENTITY) // checking for entity
        {
            std::get<0>(entity)->remove_state_flags(EntityStateFlags::ON_GROUND);
            std::get<0>(entity)->remove_state_flags(EntityStateFlags::IS_SUPPORTING);
        }
    }

    sanitize_queue(); // remove all objects that are invalid for collisions

    if (m_entity_queue.size() >= 2)
    {
        // solve collisions with multiple iterations
        for (uint32_t i = 0; i < m_iterations; i++)
        {
            calc_collisions(); 
            for (const auto &entity : m_entity_queue)
            {
                integrate_forces(std::get<1>(entity), std::get<3>(entity), m_substep_delta_time / 2.0);
            }
        }
    }

    m_entity_queue.clear();
}

void PhysicsSystem::sanitize_queue()
{
    std::vector<ComponentTuple>::iterator iter;
    for (iter = m_entity_queue.begin(); iter != m_entity_queue.end(); ) 
    {
        if ((std::get<0>(*iter) == NULL_ENTITY) || (std::get<2>(*iter) == NULL_COLLIDER))
        {
            iter = m_entity_queue.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void PhysicsSystem::calc_collisions() const
{
    for (uint32_t i = 0; i < m_entity_queue.size() - 1; i++)
    {
        for (uint32_t j = i + 1; j < m_entity_queue.size(); j++)
        {
            resolve_collision(m_entity_queue.at(i), m_entity_queue.at(j));            
        }
    }
}

glm::vec2 PhysicsSystem::calc_mt_vec(const Ptr<const BoxCollider2DComponent> &col_1, const Ptr<const BoxCollider2DComponent> &col_2, const Ref<Transform2DComponent> pos_1, const Ref<Transform2DComponent> pos_2) const
{
    glm::vec2 output(0.0f);

    const float a_l = static_cast<float>(pos_1.get().x) - (col_1.get()->width * col_1.get()->scale);
    const float a_r = static_cast<float>(pos_1.get().x) + (col_1.get()->width * col_1.get()->scale);
    const float b_l = static_cast<float>(pos_2.get().x) - (col_2.get()->width * col_2.get()->scale);
    const float b_r = static_cast<float>(pos_2.get().x) + (col_2.get()->width * col_2.get()->scale);

    const float a_t = static_cast<float>(pos_1.get().y) + (col_1.get()->height * col_1.get()->scale);
    const float a_b = static_cast<float>(pos_1.get().y) - (col_1.get()->height * col_1.get()->scale);
    const float b_t = static_cast<float>(pos_2.get().y) + (col_2.get()->height * col_2.get()->scale);
    const float b_b = static_cast<float>(pos_2.get().y) - (col_2.get()->height * col_2.get()->scale);

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
    const auto [entity1, physics_1, collider_1, transform_1] = ent1;
    const auto [entity2, physics_2, collider_2, transform_2] = ent2;

    if (physics_1.get().has_flags(PhysicsFlags::STATIC) && physics_2.get().has_flags(PhysicsFlags::STATIC))
    {   // bro whatchu even doin here
        return;
    }
    const glm::vec2 mtv = calc_mt_vec(collider_1, collider_2, transform_1, transform_2);
    if (mtv.x == 0.0f && mtv.y == 0.0f) 
    {
        return;
    }
    const glm::vec2 relative_velocity          = physics_1.get().velocity - physics_2.get().velocity;
    const glm::vec2 collision_normal           = glm::normalize(mtv);
    const float relative_velocity_along_normal = glm::dot(relative_velocity, collision_normal);
    if (relative_velocity_along_normal < 0.0f) 
    {
        return;
    }
    const float e = std::min(physics_1.get().restitution, physics_2.get().restitution);
    const float impulse_magnitude = -(1.0f + e) * relative_velocity_along_normal / static_cast<float>(m_substep_delta_time) / 2.0f;

    // friction
    const glm::vec2 friction_direction          = { -collision_normal.y, collision_normal.x };
    const float relative_velocity_along_surface = glm::dot(relative_velocity, friction_direction);
    const float friction_amount                 = impulse_magnitude * (physics_1.get().friction + physics_2.get().friction) / 2.0f;
    const glm::vec2 kinetic_friction            = glm::sign(relative_velocity_along_surface) * friction_direction * friction_amount;
    const glm::vec2 static_friction             = kinetic_friction * 1.5f; // very rough approximation

    const float kinetic_friction_treshold = 1e-1F * 2;
    const float static_friction_treshold = 1e-2F;
    const glm::vec2 friction_force = std::abs(relative_velocity_along_surface) > kinetic_friction_treshold
        ? kinetic_friction
        : std::abs(relative_velocity_along_surface) > static_friction_treshold
            ? static_friction
            : glm::vec2(0.0f);

    // correcting positions
    const float percent           = std::max(0.35f / m_iterations, 0.01f);
    const float slop              = 0.04f;
    const float penetration_depth = std::max(std::max(std::abs(mtv.x), std::abs(mtv.y)) - slop, 0.0f);
    const float correction_amount = penetration_depth * percent * 0.1f;
    const glm::vec2 correction    = collision_normal * correction_amount;

    // Debugging print statements
    //std::cout << "Friction Direction: " << friction_direction.x << ", " << friction_direction.y << std::endl;
    //std::cout << "Relative Velocity Along Surface: " << relative_velocity_along_surface << std::endl;
    //std::cout << "Friction Force: " << friction_force.x << ", " << friction_force.y << std::endl;

    // applying changes
    if (physics_1.get().has_flags(PhysicsFlags::STATIC))
    {
        physics_2.get().forces -= impulse_magnitude * collision_normal * 2.0f;
        physics_2.get().forces -= friction_force;
        transform_2.get().x    += correction.x;
        transform_2.get().y    += correction.y;
    }
    else if (physics_2.get().has_flags(PhysicsFlags::STATIC))
    {
        physics_1.get().forces += impulse_magnitude * collision_normal * 2.0f;
        physics_1.get().forces += friction_force;
        transform_1.get().x    -= correction.x;
        transform_1.get().y    -= correction.y;
    }
    else
    {
        physics_1.get().forces += impulse_magnitude * collision_normal;
        physics_1.get().forces += friction_force;
        physics_2.get().forces -= impulse_magnitude * collision_normal;
        physics_2.get().forces -= friction_force;

        const float mass_ratio_1 = physics_2.get().mass / (physics_1.get().mass + physics_2.get().mass);
        const float mass_ratio_2 = physics_1.get().mass / (physics_1.get().mass + physics_2.get().mass);

        transform_1.get().x -= correction.x * mass_ratio_1;
        transform_1.get().y -= correction.y * mass_ratio_1;
        transform_2.get().x += correction.x * mass_ratio_2;
        transform_2.get().y += correction.y * mass_ratio_2;
    }

    // setting flags
    if (collision_normal.x == 0)
    {
        if (collision_normal.y < 0.0f)
        {
            entity1->set_state_flags(EntityStateFlags::ON_GROUND);
            entity2->set_state_flags(EntityStateFlags::IS_SUPPORTING);
        }
        else
        {
            entity2->set_state_flags(EntityStateFlags::ON_GROUND);
            entity1->set_state_flags(EntityStateFlags::IS_SUPPORTING);
        }
    }
}

void PhysicsSystem::add_gravity(const Ref<PhysicsComponent> physics) const
{
    physics.get().temp_acc.y -= Settings::GRAVITY_STRENGTH * static_cast<float>(Settings::UPDATE_TIME_MS);
}

static inline glm::vec2 calc_euler_velocity(const glm::vec2 &velocity, const glm::vec2 &temp_acceleration, const glm::vec2 &forces, float mass, float h)
{
    const glm::vec2 acceleration = forces / mass;
    return velocity + temp_acceleration + acceleration * h;
}

void PhysicsSystem::integrate_forces(const Ref<PhysicsComponent> physics, const Ref<Transform2DComponent> transform, double h) const
{
#ifdef PHYSICS_SOLVER_EULER

    transform.get().x      += static_cast<double>(physics.get().velocity.x) * h;
    transform.get().y      += static_cast<double>(physics.get().velocity.y) * h;
    physics.get().velocity = calc_euler_velocity(physics.get().velocity, physics.get().temp_acc, physics.get().forces, physics.get().mass, static_cast<float>(h));
    
#elif defined(PHYSICS_SOLVER_RK4)

    // TODO :(

#endif
    physics.get().forces   = { 0.0f, 0.0f };
    physics.get().temp_acc = { 0.0f, 0.0f };
}