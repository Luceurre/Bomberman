//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_BLOCKBEHAVIOURCOMPONENT_H
#define BOMBERMAN_BLOCKBEHAVIOURCOMPONENT_H

#include "../../Utils/Tools.h"

// On met tous les comportements de blocage dans ce fichier!
class BlockBehaviourComponent : public Component {
public:
    inline virtual bool block(Entity* toBlock, int velX, int velY) {
        info("BLOCKED");

        return true;
    }
};


class BlockBehaviourWallComponent : public BlockBehaviourComponent {
public:
    inline bool block(Entity* toBlock, int velX, int velY) override {
        auto hitbox1 = &entity->getComponent<TrueHitboxComponent>();
        auto hitbox2 = &toBlock->getComponent<TrueHitboxComponent>();

        if (hitbox1 && hitbox2) {
            return rect_collide(hitbox1->getHitbox(), hitbox2->getHitbox(velX, velY));
        }

        return false;
    }
};


#endif //BOMBERMAN_BLOCKBEHAVIOURCOMPONENT_H
