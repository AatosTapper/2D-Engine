#pragma once

#include "engine/System.h"
#include "singleton.h"

#include <functional>
#include <vector>
#include <memory>

/*
How to use:

1. create a variable to hold a reference to the timer:
TimerRef my_timer = nullptr;

2. call set_timer function and assign it's return value to the reference:
my_timer = TimerSystem.instance().set_timer(num_ticks_here);

3. check the status of the timer every update:
if (my_timer != nullptr)
{
    if (my_timer->status == TIMER_STATUS::DONE)
    {
        // do stuff here
    }
}

4. also remove the timer when it's status turns to DELETE:
if (my_timer != nullptr)
{
    if (my_timer->status == TIMER_STATUS::DELETE)
    {
        my_timer = nullptr;
    }
}

*/

enum class TIMER_STATUS : uint8_t
{
    WAITING = 0u,
    RUNNING = 1u,
    DONE = 2u,
    DELETE = 3u
};

class Timer
{
public:
    Timer(uint32_t lenght_ticks_) : 
        length_ticks(lenght_ticks_), 
        status(TIMER_STATUS::WAITING) {}

    uint32_t length_ticks;

    TIMER_STATUS status;
};

using TimerRef = std::shared_ptr<const Timer>;

class TimerSystem : public System
{
public:
    void update() override;

    [[nodiscard]] TimerRef set_timer(uint32_t ticks);
    
    IMPL_VIRTUAL_SINGLETON_DISPATCHER(TimerSystem, System)

private:
    std::vector<std::shared_ptr<Timer>> timer_storage; // timer slots aren't cleared but they are reused
};
