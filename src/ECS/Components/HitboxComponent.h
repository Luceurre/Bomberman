//
// Created by pglandon on 6/1/20.
//

#ifndef BOMBERMAN_HITBOXCOMPONENT_H
#define BOMBERMAN_HITBOXCOMPONENT_H

#include "Components.h"

class TrueHitboxComponent;

// An upgrade of the Position Component, where we add a width and height.
// dependencies: Position.
// JUST FOR DRAWING!!!
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

        if (!entity->hasComponent<TrueHitboxComponent>()) {
            entity->addComponents<TrueHitboxComponent>(width, height);
        }

        positionComponent = &entity->getComponent<PositionComponent>();
    }
};

// For physics (because assets hitboxes != physics hitboxes...)
class TrueHitboxComponent : public Component {
public:
    // Shifting from top left by default!
    int shiftx, shifty, width, height;
    PositionComponent* positionComponent;
    HitboxComponent* hitboxComponent;

    inline TrueHitboxComponent(int w, int h, int sx, int sy) {
        shiftx = sx;
        shifty = sy;
        width = w;
        height = h;

        positionComponent = nullptr;
    }

    inline TrueHitboxComponent(int w, int h) : TrueHitboxComponent(w, h, 0, 0) {

    }

    inline void init() override {
        if (!entity->hasComponent<PositionComponent>()) {
            entity->addComponents<PositionComponent>();
            warn("default position");
        }

        positionComponent = &entity->getComponent<PositionComponent>();
    }

    inline SDL_Rect getHitbox() {
        return SDL_Rect{positionComponent->posX + shiftx, positionComponent->posY + shifty, width, height};
    }

    inline SDL_Rect getHitbox(int vx, int vy) {
        return SDL_Rect{positionComponent->posX + shiftx + vx, positionComponent->posY + shifty + vy, width, height};
    }
};


#endif //BOMBERMAN_HITBOXCOMPONENT_H
