//
// Created by pglandon on 6/9/20.
//

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "../Components/Components.h"

#define TEX_PATH "assets/player.png"

inline Entity* makePlayer(Manager& manager) {
    auto& entity(manager.addEntity());

    int posX[4] = {0, 1, 2, 3};
    int posY[4] = {0, 0, 0, 0};
    int ticks[4] = {20, 20, 20, 20};

    entity.addComponents<AnimationComponent>(TEX_PATH, 32, 32, posX, posY, ticks, 4);

    return &entity;
}


#endif //BOMBERMAN_PLAYER_H
