#pragma once

#include <iostream>
#include "config.h"

class Scene;

class GameObject
{
public:
    using id_t = uint64_t;
    id_t get_id() const { return id; }

    GameObject() : id(create_id()) {}
    virtual ~GameObject() {}

    // override these functions to add custom behaviour to inherited game objects
    // each function is ran automatically:
    virtual void on_attach() {}   // when object is added to a scene
    virtual void on_update() {}   // when object is updated in the gameloop
    virtual void on_destroy() {}  // when object is deleted from a scene
    // override this to call component update/queue functions
    virtual void update_components() {}; // after all objects are updated in the gameloop    
    
private:
    const id_t id;

    id_t create_id()
    {
        static id_t cur_id = 0u;
        return cur_id++;
    }
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