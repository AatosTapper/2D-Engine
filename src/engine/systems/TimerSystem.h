#pragma once

#include "../System.h"

#include <functional>
#include <vector>
#include <memory>

class Timer
{
public:
    Timer(uint32_t lenght_ticks_) : 
        length_ticks(lenght_ticks_), 
        status(STATUS::WAITING) {}

    uint32_t length_ticks;

    enum class STATUS
    {
        WAITING = 0u,
        RUNNING = 1u,
        DONE = 2u
    } status;
};

using SignalFunction = std::function<Timer::STATUS()>;

class TimerSystem : public System
{
public:
    void update() override;

    SignalFunction set_timer(uint32_t ticks);
    
    static System &get_base_instance();
    static TimerSystem &instance();

private:
    std::vector<std::unique_ptr<Timer>> timers;
};
