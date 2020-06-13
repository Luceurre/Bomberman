//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_BLOCKCOMPONENT_H
#define BOMBERMAN_BLOCKCOMPONENT_H

#include "Components.h"
#include "../../Utils/Direction.h"

// Physique de l'entité, comment elle se comporte face aux autres composants qui se déplace
class BlockComponent : public Component {
public:
    bool shouldBlock = true;
    BlockBehaviourComponent* blockBehaviorComponentNoInit;
    BlockBehaviourComponent* blockBehaviorComponent;

    inline BlockComponent(BlockBehaviourComponent* behaviour) {
        blockBehaviorComponentNoInit = behaviour;
    }

    inline void init() override {
        entity->addComponents<BlockBehaviourComponent>(blockBehaviorComponentNoInit);
        blockBehaviorComponent = &entity->getComponent<BlockBehaviourComponent>();
    }

    inline bool handle_block(Entity* toBlock, int velX, int velY) {
        if (shouldBlock)
            return blockBehaviorComponent->block(toBlock, velX, velY);
    }
};


#endif //BOMBERMAN_BLOCKCOMPONENT_H
