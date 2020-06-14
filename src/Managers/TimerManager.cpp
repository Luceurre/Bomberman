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

bool Timer::isActive() {
    return active;
}
