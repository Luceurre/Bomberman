//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_BLOCKCOMPONENT_H
#define BOMBERMAN_BLOCKCOMPONENT_H

#include "Components.h"
#include "../../Utils/Direction.h"

// Physique de l'entité, comment elle se comporte face aux autres composants qui se déplacent
class BlockComponent : public Component {
public:
    bool shouldBlock;

    inline BlockComponent(bool block) {
        shouldBlock = block;
    }

    inline bool handle_block(Entity* toBlock, int velX, int velY) {
        return shouldBlock;
    }
};


#endif //BOMBERMAN_BLOCKCOMPONENT_H
