//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_VELOCITYCOMPONENT_H
#define ATELIERPROG_VELOCITYCOMPONENT_H


#include "Components.h"

class VelocityComponent : public Component {
public:
    int velX, velY;

    inline VelocityComponent() {
        velX = 0;
        velY = 0;
    }

    inline VelocityComponent(int vx, int vy) {
        velX = vx;
        velY = vy;
    }

};


#endif //ATELIERPROG_VELOCITYCOMPONENT_H
