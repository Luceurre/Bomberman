//
// Created by pglan on 14/06/2020.
//

#ifndef BOMBERMAN_TIMERMANAGER_H
#define BOMBERMAN_TIMERMANAGER_H

#include "../Events/EventCore.h"

class Timer {
private:
    int currentTick;
    int activateTick;
    cb::Callback0<bool> callback;
    bool active;
public:

    void update();
    bool isActive();
};

class TimerManager {

};


#endif //BOMBERMAN_TIMERMANAGER_H
