//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_BLOCKBEHAVIOURCOMPONENT_H
#define BOMBERMAN_BLOCKBEHAVIOURCOMPONENT_H


class BlockBehaviourComponent : public Component {
public:
    inline virtual bool block(Entity* toBlock, int velX, int velY) {
        return true;
    }
};


#endif //BOMBERMAN_BLOCKBEHAVIOURCOMPONENT_H
