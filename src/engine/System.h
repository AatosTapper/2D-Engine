#pragma once

class System
{
public:
    virtual ~System() {}

    virtual void update() = 0; // override this to implement custom logic

protected:
    System() {}
public:
    // deleting these to enforce singleton pattern
    System(System const&) = delete;
    void operator=(System const&) = delete;
};

/*
    a definition of a system is in the docs document
*/

/*
How to create a system:

Implement everything like this for your system and then freely add custom logic
and new variables etc. This way the system will work as intended in all places.

-----------------------------------------------------------
CollisionSystem.h file:
#include "engine/System.h"
#include "singleton.h"              // notice this include!

class CollisionSystem : public System
{
public:
    void update() override;

    IMPL_VIRTUAL_SINGLETON_DISPATCHER(CollisionSystem, System)      // and this macro!
};

-----------------------------------------------------------
CollisionSystem.cpp file:

void CollisionSystem::update()
{
    // update logic here
}

*/
