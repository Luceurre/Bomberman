//
// Created by pglandon on 6/1/20.
//

#ifndef BOMBERMAN_HITBOXCOMPONENT_H
#define BOMBERMAN_HITBOXCOMPONENT_H

#include "Components.h"

// An upgrade of the Position Component, where we add a width and height.
// dependencies: Position.
class HitboxComponent : public Component {
public:
    int width, height;
    PositionComponent* positionComponent;

    inline HitboxComponent(int w, int h) : width(w), height(h) {
        positionComponent = nullptr;
    }

    inline HitboxComponent() : HitboxComponent(0, 0) {

    }

    inline void init() override {
        if (!entity->hasComponent<PositionComponent>()) {
            warn("using default Position.");
            entity->addComponents<PositionComponent>();
        }

        positionComponent = &entity->getComponent<PositionComponent>();
    }
};


#endif //BOMBERMAN_HITBOXCOMPONENT_H
