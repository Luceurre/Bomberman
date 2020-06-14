//
// Created by pglan on 14/06/2020.
//

#include "TimerManager.h"

void Timer::update() {
    if (active) {
        currentTick++;
        if (currentTick > activateTick) {
            currentTick = 0;
            active = callback();
        }
    }

}

bool Timer::isActive() const {
    return active;
}

Timer::Timer(int tickRate, const cb::Callback0<bool>& call) {
    activateTick = tickRate;
    currentTick = 0;
    active = true;
    callback = call;
}

void Timer::reset() {
    currentTick = 0;
}

void TimerManager::addTimer(Timer *timer) {
    std::unique_ptr<Timer> ptr{timer};
    timers.emplace_back(std::move(ptr));
}

void TimerManager::updateTimers() {
    for (auto& it : timers) {
        it->update();
    }

    timers.erase(std::remove_if(std::begin(timers), std::end(timers), [](std::unique_ptr<Timer>& timer) {
        return !timer->isActive();
    }), std::end(timers));
}
