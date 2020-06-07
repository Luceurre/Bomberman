//
// Created by pglandon on 6/7/20.
//

#ifndef BOMBERMAN_MOUSEPOSITIONCOMPONENT_H
#define BOMBERMAN_MOUSEPOSITIONCOMPONENT_H

#include "Components.h"

class MousePositionComponent : public Component {
public:
    int mouseX, mouseY;

    inline void handleEvent(const SDL_Event& event) override {
        if (event.type == SDL_MOUSEMOTION) {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
    }
};


#endif //BOMBERMAN_MOUSEPOSITIONCOMPONENT_H
