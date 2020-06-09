//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_BACKGROUND_H
#define ATELIERPROG_BACKGROUND_H


#include "../Components/Components.h"

inline Entity* makeBackground(Manager& manager, SDL_Renderer* renderer, std::string tex_path) {
    auto& entity(manager.addEntity());

    entity.addComponents<BasicSpriteComponent>(tex_path);

    return &entity;
}


#endif //ATELIERPROG_BACKGROUND_H
