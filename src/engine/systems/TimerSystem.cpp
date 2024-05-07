#include "TimerSystem.h"

System &TimerSystem::get_base_instance()
{
    return dynamic_cast<System&>(instance());
}

TimerSystem &TimerSystem::instance()
{
    static TimerSystem instance;
    return instance;
}

SignalFunction TimerSystem::set_timer(uint32_t ticks)
{
    auto timer = std::make_unique<Timer>(ticks);
    Timer *ptr = timer.get();
    timers.push_back(std::move(timer));

    return [ptr]() -> Timer::STATUS {
        if (ptr == nullptr) return Timer::STATUS::DONE;
        return ptr->status;
    };
}

void TimerSystem::update()
{
    for (auto &timer : timers)
    {
        if (timer->status == Timer::STATUS::DONE)
        {
            timer.reset(); // WARNING THIS DOESN'T CLEAR THE POINTER FROM THE VECTOR
        }
        if (timer->length_ticks > 0u)
        {
            timer->status = Timer::STATUS::RUNNING;
        }
        else
        {
            timer->status = Timer::STATUS::WAITING;
        }
        if (timer->status == Timer::STATUS::RUNNING)
        {
            timer->length_ticks--;
            if (timer->length_ticks == 0u)
            {
                timer->status = Timer::STATUS::DONE;
            }
        }
    }
}