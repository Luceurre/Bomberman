//
// Created by pglandon on 6/14/20.
//

#ifndef BOMBERMAN_SELFDESTRUCTCOMPONENT_H
#define BOMBERMAN_SELFDESTRUCTCOMPONENT_H

#include "Components.h"
#include "../../Managers/TimerManager.h"

class SelfDestructComponent : public Component {
int destructionTick;

public:
    inline SelfDestructComponent(int activationTick) {
        destructionTick = activationTick;
    }

    inline void init() override {
        auto timerManager = &TimerManager::getInstance();
        timerManager->addTimer(new Timer(destructionTick, cb::Make0(this, &SelfDestructComponent::destruct)));
    }

    inline bool destruct() {
        entity->active = false;

        return false;
    }
};


#endif //BOMBERMAN_SELFDESTRUCTCOMPONENT_H
