//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_VELOCITYCOMPONENT_H
#define ATELIERPROG_VELOCITYCOMPONENT_H


#include "Components.h"

class VelocityComponent : public Component {
protected:
    inline std::string descriptor() override {
        return "(VelocityComponent)";
    }
public:
    // in pixel per tick.
    int velX, velY;
    PositionComponent* positionComponent;

    inline VelocityComponent() {
        velX = 0;
        velY = 0;
    }

    inline VelocityComponent(int vx, int vy) {
        velX = vx;
        velY = vy;
    }

    inline void init() override {
        if (!entity->hasComponent<PositionComponent>()) {
            warn("Using default position.");
            entity->addComponents<PositionComponent>();
        }
        positionComponent = &entity->getComponent<PositionComponent>();
    }

    inline void update() override {
        positionComponent->posX += velX;
        positionComponent->posY += velY;
    }

};


#endif //ATELIERPROG_VELOCITYCOMPONENT_H
