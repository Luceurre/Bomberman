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
    BlockBehaviourComponent* blockBehaviourComponentNoInit;
    BlockBehaviourComponent* blockBehaviourComponent;

    inline BlockComponent(BlockBehaviourComponent* behaviourComponent) {
        shouldBlock = true;
        blockBehaviourComponentNoInit = behaviourComponent;
        blockBehaviourComponent = nullptr;
    }

    inline void init() override {
        entity->addComponents<BlockBehaviourComponent>(blockBehaviourComponentNoInit);
        blockBehaviourComponent = &entity->getComponent<BlockBehaviourComponent>();
    }

    inline bool handle_block(Entity* toBlock, int velX, int velY) {
        if (shouldBlock)
            return blockBehaviourComponent->block(toBlock, velX, velY);
        return false;
    }

};


#endif //BOMBERMAN_BLOCKCOMPONENT_H
