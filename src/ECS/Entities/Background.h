//
// Created by pglandon on 6/1/20.
//

#ifndef ATELIERPROG_BACKGROUND_H
#define ATELIERPROG_BACKGROUND_H


#include "../Components/Components.h"

inline DrawableEntity* makeBackground(Manager& manager, SDL_Renderer* renderer, std::string tex_path) {
    auto& entity(manager.addDrawableEntity());

    entity.addComponents<BasicSpriteComponent>(tex_path, renderer);

    return &entity;
}


#endif //ATELIERPROG_BACKGROUND_H
