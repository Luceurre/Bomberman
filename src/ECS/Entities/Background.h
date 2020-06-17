//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_BACKGROUND_H
#define ATELIERPROG_BACKGROUND_H


#include "../Components/Components.h"

#define BACKGROUND_TEX_PATH "assets/background.jpg"

inline Entity* makeBackground(Manager& manager, SDL_Renderer* renderer) {
    auto& entity(manager.addEntity(0));

    entity.addComponents<BasicSpriteComponent>(BACKGROUND_TEX_PATH);

    return &entity;
}


#endif //ATELIERPROG_BACKGROUND_H
