//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_POSITIONCOMPONENT_H
#define ATELIERPROG_POSITIONCOMPONENT_H


#include "Components.h"

class PositionComponent : public Component {
public:
    int posX, posY;

    inline PositionComponent() {
        posX = 0;
        posY = 0;
    }

    inline PositionComponent(int x, int y) {
        posX = x;
        posY = y;
    }
};


#endif //ATELIERPROG_POSITIONCOMPONENT_H
