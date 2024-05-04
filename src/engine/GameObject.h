#pragma once

#include <iostream>
#include "../config.h"

class Scene;

class GameObject
{
public:
    using id_t = uint64_t;
    id_t get_id() const { return id; }

    GameObject() : id(create_id()) {}
    virtual ~GameObject() {}

    // override these functions to add custom behaviour to inherited game objects
    // each function is ran automatically when:
    virtual void on_attach(Scene *scene) {(void)scene;}   // object is added to a scene
    virtual void on_update(Scene *scene) {(void)scene;}   // object is updated in the gameloop
    virtual void on_destroy(Scene *scene) {(void)scene;}  // object is deleted from a scene

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

    void on_attach(Scene *scene) override;
    void on_update(Scene *scene) override;
    void on_destroy(Scene *scene) override;
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

void EnemyGameObject::on_attach(Scene *scene)
{
    // some functionality
}

void EnemyGameObject::on_update(Scene *scene)
{
    // some functionality
}

void EnemyGameObject::on_destroy(Scene *scene)
{
    // some functionality
}

*/