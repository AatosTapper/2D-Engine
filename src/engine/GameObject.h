#pragma once

#include <stdint.h>

class GameObject
{
public:
    using id_t = uint64_t;
    id_t get_id() const { return id; }

    GameObject() : id(create_id()) {}
    virtual ~GameObject() {}

    // override these functions to add custom behaviour to inherited game objects
    // each function is ran automatically when:
    virtual void on_create() {}   // object is added to a scene
    virtual void on_update() {}   // object is updated in the gameloop
    virtual void on_destroy() {}  // object is deleted from a scene

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

    int some_enemy_variable;
    bool other_enemy_variable;
    glm::vec2 another_enemy_variable_with_arbitary_name;

    void on_create() override;
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

void EnemyGameObject::on_create()
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