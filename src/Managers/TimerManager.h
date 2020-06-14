//
// Created by pglan on 14/06/2020.
//

#ifndef BOMBERMAN_TIMERMANAGER_H
#define BOMBERMAN_TIMERMANAGER_H

#include <memory>
#include "../Events/EventCore.h"
#include "../Utils/Logger.h"

class Timer {
private:
    int currentTick;
    int activateTick;
    cb::Callback0<bool> callback;
    bool active;
public:
    Timer(int tickRate, const cb::Callback0<bool>& call);
    void update();
    [[nodiscard]] bool isActive() const;
    void reset();
};

class TimerManager : public Logger {
private:
    inline TimerManager() = default;
    std::vector<std::unique_ptr<Timer>> timers;

protected:
    inline std::string descriptor() override {
        return "(TimerManager)";
    }
public:
    static TimerManager& getInstance()
    {
        static TimerManager instance;
        return instance;
    }

    TimerManager(TimerManager const&) = delete;
    void operator=(TimerManager const&) = delete;

    void addTimer(Timer* timer);
    void updateTimers();
};


#endif //BOMBERMAN_TIMERMANAGER_H
