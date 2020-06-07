//
// Created by pglandon on 6/7/20.
//

#ifndef BOMBERMAN_CLICKABLECOMPONENT_H
#define BOMBERMAN_CLICKABLECOMPONENT_H

#include "Components.h"
#include "../../Utils/Functor.h"

class ClickableComponent : public Component {
protected:
    Functor0<void>* callbackMethod;

public:
    MousePositionComponent* mousePositionComponent;
    HitboxComponent* hitboxComponent;

    inline ClickableComponent(Functor0<void>* callback) {
        callbackMethod = callback;
    }

    inline void init() override {
        if (!entity->hasComponent<MousePositionComponent>()) {
            entity->addComponents<MousePositionComponent>();
        }
        mousePositionComponent = &entity->getComponent<MousePositionComponent>();

        if (!entity->hasComponent<HitboxComponent>()) {
            entity->addComponents<HitboxComponent>();
            warn("Default Hitbox!");
        }

        hitboxComponent = &entity->getComponent<HitboxComponent>();
    }

    inline void handleEvent(const SDL_Event& event) override {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (hitboxComponent->positionComponent->posX <= mousePositionComponent->mouseX
            && mousePositionComponent->mouseX < hitboxComponent->positionComponent->posX + hitboxComponent->width
            && hitboxComponent->positionComponent->posY <= mousePositionComponent->mouseY
            && mousePositionComponent->mouseY < hitboxComponent->positionComponent->posY + hitboxComponent->height) {
                (*callbackMethod)();
            }
        }
    }
};


#endif //BOMBERMAN_CLICKABLECOMPONENT_H
