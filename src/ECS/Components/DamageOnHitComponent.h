//
// Created by pglandon on 6/14/20.
//

#ifndef BOMBERMAN_DAMAGEONHITCOMPONENT_H
#define BOMBERMAN_DAMAGEONHITCOMPONENT_H

#include "Components.h"
#include "HealPointComponent.h"

class DamageOnHitComponent : public Component {
private:
    int damage;
    Group targetedGroup;
    Manager* manager;

public:
    TrueHitboxComponent* hitboxComponent;

    inline DamageOnHitComponent(Manager* manager, Group target, int damage) {
        this->damage = damage;
        targetedGroup = target;
        this->manager = manager;
    }

    inline void init() override {
        if (!entity->hasComponent<TrueHitboxComponent>()) {
            error("No hitbox detected!");
            exit(-1);
        }

        hitboxComponent = &entity->getComponent<TrueHitboxComponent>();
    }

    inline void update() override {
        for (auto& it : manager->getGroup(targetedGroup)) {
            if (it->hasComponent<TrueHitboxComponent>() && it->hasComponent<HealPointComponent>()) {
                auto hitbox = &it->getComponent<TrueHitboxComponent>();

                if (rect_collide(hitbox->getHitbox(), hitboxComponent->getHitbox())) {
                    it->getComponent<HealPointComponent>().takeDamage(damage);
                }
            }
        }
    }
};


#endif //BOMBERMAN_DAMAGEONHITCOMPONENT_H
