#pragma once

#include <iostream>
#include <memory>
#include "config.h"

#define CREATE_GAME_OBJECT(T) std::make_unique<T>()
#define CREATE_GAME_OBJECT_WITH_ARGS(T, args) std::make_unique<T>(args)

using Bitflag = uint64_t;

// Flags for gameobjects, represented with each bit being a single flag like this: 0000 0011 0001 1010
// Add new ones like this: NEW_FLAG = LAST_FLAG << 1
// You can combine flags with bitwise OR like this: ObjectFlags::NPC | ObjectFlags::FRIENDLY | etc
enum ObjectFlags : Bitflag
{
    PLAYER      = 1u,
    NPC         = PLAYER << 1,
    FRIENDLY    = NPC << 1,
    HOSTILE     = FRIENDLY << 1
};

class GameObject
{
public:
    using id_t = uint64_t;

    [[nodiscard]] id_t get_id() const       { return id; }
    
    // flags
    void set_flags(ObjectFlags flag)        { flags |= flag; }
    void remove_flags(ObjectFlags flag)     { flags &= ~flag; }
    [[nodiscard]] bool has_flags(ObjectFlags flag) const { return 0 != (flags & flag); }

    // overridable functions
    virtual void on_attach()                {}  // is ran when object is added to a scene
    virtual void on_update()                {}  // is ran when object is updated in the gameloop
    virtual void on_destroy()               {}  // is ran when object is deleted from a scene

    // override this to call component update/queue functions
    virtual void update_components()        {}; // after all objects are updated in the gameloop    
    
private:
    const id_t id;
    Bitflag flags{0};

    id_t create_id()
    {
        static id_t cur_id = 0u;
        return cur_id++;
    }

public:
    // constructor and destructor, just implementation stuff
    GameObject() : id(create_id())          {}
    virtual ~GameObject()                   {}
};


/*
How to create a new type of game object (like an enemy or a weapon):

-------------------------
EnemyGameObject.h file:
-------------------------

class EnemyGameObject : public GameObject
{
public:
    EnemyGameObject();
    ~EnemyGameObject() override;

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
EnemyGameObject.cpp file:
-------------------------

EnemyGameObject::EnemyGameObject()
{
    // you can set flags here (or elsewhere too):
    set_flag(ObjectFlags::NPC | ObjectFlags::HOSTILE);
}

EnemyGameObject::~EnemyGameObject()
{

}

void EnemyGameObject::update_components()
{
    some_component.update(); // calling the component's update function

    // sending the component to it's corresponding system if needed
    EnemyControllerSystem::instance().queue_contorller(&some_component);
    Renderer::instance().queue_sprite({ &sprite, transform.get_matrix() });
}

void EnemyGameObject::on_attach()
{
    // some functionality
}

void EnemyGameObject::on_update()
{
    // some functionality
}

void EnemyGameObject::on_destroy()
{
    // some functionality
}

*/