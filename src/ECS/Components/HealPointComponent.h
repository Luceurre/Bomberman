//
// Created by pglandon on 6/14/20.
//

#ifndef BOMBERMAN_HEALPOINTCOMPONENT_H
#define BOMBERMAN_HEALPOINTCOMPONENT_H

#include "Components.h"
#include "../../Managers/EventManager.h"

class HealPointComponent : public Component {
public:
    int hp;
    int invicibilityInTicks;
    int lastTakenDamage;
    Event* deathEvent;

    inline HealPointComponent(int hp, int invTicks, Event* deathEvent) {
        this->hp = hp;
        this->invicibilityInTicks = invTicks;
        lastTakenDamage = 0;
        this->deathEvent = deathEvent;
    }

    inline void takeDamage(int dmg) {

        if (lastTakenDamage < invicibilityInTicks)
            return;

        info("taking damage...");
        hp -= dmg;

        if (hp > 0) {
            lastTakenDamage = 0;
        } else {
            EventManager::getInstance()->push_event(deathEvent);
        }
    }

    inline void update() override {
        lastTakenDamage++;
    }
};


#endif //BOMBERMAN_HEALPOINTCOMPONENT_H
