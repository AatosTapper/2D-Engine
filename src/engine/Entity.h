#pragma once

#include <iostream>
#include <memory>
#include "config.h"

#define CREATE_ENTITY(T) std::make_unique<T>()
#define CREATE_ENTITY_WITH_ARGS(T, args) std::make_unique<T>(args)

using Bitflag = uint64_t;

// Flags for entities, represented with each bit being a single flag like this: 0000 0011 0001 1010
// Add new ones like this: NEW_FLAG = LAST_FLAG << 1
// You can combine flags with bitwise OR like this: EntityFlags::NPC | EntityFlags::FRIENDLY | etc
enum EntityFlags : Bitflag
{
    PLAYER      = 1u,
    NPC         = PLAYER << 1,
    FRIENDLY    = NPC << 1,
    HOSTILE     = FRIENDLY << 1
};

class Entity
{
public:
    using id_t = uint64_t;

    [[nodiscard]] id_t get_id() const { return id; }
    
    // flags
    constexpr void set_flags(EntityFlags flag) { flags |= flag; }
    constexpr void remove_flags(EntityFlags flag) { flags &= ~flag; }
    [[nodiscard]] constexpr bool has_flags(EntityFlags flag) const { return 0 != (flags & flag); }

    // overridable functions
    virtual void on_attach() {}  // is ran when entity is added to a scene
    virtual void on_update() {}  // is ran when entity is updated in the gameloop
    virtual void on_destroy() {}  // is ran when entity is deleted from a scene

    // override this to call component update/queue functions
    virtual void update_components() {}; // after all entities are updated in the gameloop    
    
private:
    const id_t id;
    Bitflag flags{0};

    id_t create_id()
    {
        static id_t cur_id = 0u;
        return cur_id++;
    }

public:
    Entity() : id(create_id()) {}
    virtual ~Entity() {}
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