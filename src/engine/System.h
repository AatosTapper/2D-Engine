#pragma once

/*
    a definition of a system is in the docs document
*/

class System
{
public:
    virtual ~System() {}

    virtual void update() = 0; // override this to implement custom logic

protected:
    System() {}
};


/*
How to create a system:

Implement everything like this for your system and then freely add custom logic
and new variables etc. This way the system will work as intended in all places.

-----------------------------------------------------------
CollisionSystem.h file:

class CollisionSystem : public System
{
public:
    void update() override;

    static System *get_base_instance();     // notice this
    static CollisionSystem *instance();     // this

private:
    static CollisionSystem *instance;       // and this
};

-----------------------------------------------------------
CollisionSystem.cpp file:

CollisionSystem *CollisionSystem::instance = nullptr; // we need to init the instance variable like this

System *CollisionSystem::get_base_instance()          // then implement the instance function like this
{
    if (instance == nullptr)
    {
        instance = new CollisionSystem();
    }
    return dynamic_cast<System*>(instance);
}

CollisionSystem *CollisionSystem::instance()      // and this one like this
{
    if (instance == nullptr)
    {
        instance = new CollisionSystem();
    }
    return instance;
}

void CollisionSystem::update()                         // now add custom logic can go here
{
    // update logic here
}

*/
