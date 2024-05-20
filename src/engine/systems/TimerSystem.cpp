#include "TimerSystem.h"

#include <iostream>

TimerRef TimerSystem::set_timer(uint32_t ticks)
{
    auto timer = std::make_shared<Timer>(ticks);
    bool found_slot = false;
    for (auto &slot : m_timer_storage)
    {
        if (slot == nullptr)
        {
            slot = timer;
            found_slot = true;
            break;
        }
    }
    if (!found_slot)
    {
        m_timer_storage.push_back(timer);
    }

    return timer;
}

void TimerSystem::update()
{
    for (auto &timer : m_timer_storage)
    {
        if (timer == nullptr) continue;

        if (timer->status == TIMER_STATUS::DELETE)
        {
            timer = nullptr;
            continue;
        }
        if (timer->status == TIMER_STATUS::DONE)
        {
            timer->status = TIMER_STATUS::DELETE;
        }
        if (timer->length_ticks > 0u)
        {
            timer->status = TIMER_STATUS::RUNNING;
        }
        if (timer->status == TIMER_STATUS::RUNNING)
        {
            timer->length_ticks--;
            if (timer->length_ticks == 0u)
            {
                timer->status = TIMER_STATUS::DONE;
            }
        }
    }
}