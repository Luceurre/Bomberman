//
// Created by pglandon on 6/7/20.
//

#ifndef BOMBERMAN_SPRITECOMPONENT_H
#define BOMBERMAN_SPRITECOMPONENT_H


#include "Components.h"

class SpriteComponent : public Component {
public:
    inline void init() override {
        if(!entity->hasComponent<HitboxComponent>())
    }
};


#endif //BOMBERMAN_SPRITECOMPONENT_H
