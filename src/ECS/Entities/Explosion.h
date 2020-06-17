//
// Created by pglandon on 6/14/20.
//

#ifndef BOMBERMAN_EXPLOSION_H
#define BOMBERMAN_EXPLOSION_H

#include "Entities.h"

#define FLAME_TEX_PATH "assets/flame.png"
#define FLAME_TEX_WIDTH 64
#define FLAME_TEX_HEIGHT 64
#define FLAME_PRIORITY 101
#define FLAME_DURATION_IN_TICK 200

class Explosion {

private:
    Entity** entities;
    Manager* entityManager;
    TimerManager* timerManager;

    int entityCount;
public:
    inline Explosion(Manager& manager, int centerX, int centerY, int radius) {
        entities = new Entity*[4*radius + 1];


        unique_lock<mutex> lock(manager.entitiesMutex);

        auto p2 = &manager.addEntity(FLAME_PRIORITY);


        p2->addComponents<PositionComponent>(centerX,
                                            centerY);
        p2->addComponents<SpriteComponent>(FLAME_TEX_PATH);
        p2->addComponents<HitboxComponent>(64, 64);
        p2->addComponents<TrueHitboxComponent>(64, 64);
        p2->addComponents<SelfDestructComponent>(FLAME_DURATION_IN_TICK);
        p2->addComponents<DamageOnHitComponent>(&manager, PLAYER, 1);


        // On itére sur les 4 directions
        for (int i = 0; i < 4; ++i) {
            for(int j = 1; j <= radius; j++) {
                auto p = &manager.addEntity(FLAME_PRIORITY);
                p->addComponents<PositionComponent>(centerX + j * DIRECTION[i][0] * FLAME_TEX_WIDTH,
                        centerY + j * DIRECTION[i][1] * FLAME_TEX_HEIGHT);
                p->addComponents<HitboxComponent>(64, 64);
                p->addComponents<TrueHitboxComponent>(64, 64);
                p->addComponents<SpriteComponent>(FLAME_TEX_PATH);
                p->addComponents<SelfDestructComponent>(FLAME_DURATION_IN_TICK);
                p->addComponents<DamageOnHitComponent>(&manager, PLAYER, 1);
            }
        }

        lock.unlock();
    }
};


#endif //BOMBERMAN_EXPLOSION_H
