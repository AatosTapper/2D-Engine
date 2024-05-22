#pragma once

#include <iostream>
#include <memory>
#include "config.h"
#include "Flags.h"

#define CREATE_ENTITY(T) std::make_unique<T>()
#define CREATE_ENTITY_WITH_ARGS(T, args) std::make_unique<T>(args)

class Entity
{
public:
    Entity() : m_id(create_id()) {}
    virtual ~Entity() {}
    using id_t = uint64_t;

    [[nodiscard]] id_t get_id() const { return m_id; }
    
    // flags
    constexpr void set_flags(EntityFlags flag) { m_flags |= flag; }
    constexpr void remove_flags(EntityFlags flag) { m_flags &= ~flag; }
    [[nodiscard]] constexpr bool has_flags(EntityFlags flag) const { return 0 != (m_flags & flag); }

    constexpr void set_state_flags(EntityStateFlags flag) { m_state_flags |= flag; }
    constexpr void remove_state_flags(EntityStateFlags flag) { m_state_flags &= ~flag; }
    [[nodiscard]] constexpr bool has_state_flags(EntityStateFlags flag) const { return 0 != (m_state_flags & flag); }

    // overridable functions
    virtual void on_attach() {}  // is ran when entity is added to a scene
    virtual void on_update() {}  // is ran when entity is updated in the gameloop
    virtual void on_destroy() {}  // is ran when entity is deleted from a scene

    // override this to call component update/queue functions
    virtual void update_components() {}; // after all entities are updated in the gameloop    
    
private:
    const id_t m_id;
    Bitflag m_flags = 0u;
    Bitflag m_state_flags = 0u;

    id_t create_id()
    {
        static id_t cur_id = 0u;
        return cur_id++;
    }
};


/*
How to create a new type of entity (like an enemy or a weapon):

-------------------------
EnemyEntity.h file:
-------------------------

class EnemyEntity : public Entity
{
public:
    EnemyEntity();
    ~EnemyEntity() override;

    EnemyControllerComponent some_component;
    int some_enemy_variable;
    bool other_enemy_variable;
    glm::vec2 another_enemy_variable_with_arbitary_name;

    void update_components() override;

    void on_attach() override;
    void on_update() override;
    void on_destroy() override;
};

-------------------------
EnemyEntity.cpp file:
-------------------------

EnemyEntity::EnemyEntity()
{
    // you can set flags here (or elsewhere too):
    set_flag(EntityFlags::NPC | EntityFlags::HOSTILE);
}

EnemyEntity::~EnemyEntity()
{

}

void EnemyEntity::update_components()
{
    some_component.update(); // calling the component's update function

    // sending the component to it's corresponding system if needed
    EnemyControllerSystem::instance().queue_contorller(&some_component);
    Renderer::instance().queue_sprite({ &sprite, transform.get_matrix() });
}

void EnemyEntity::on_attach()
{
    // some functionality
}

void EnemyEntity::on_update()
{
    // some functionality
}

void EnemyEntity::on_destroy()
{
    // some functionality
}

*/