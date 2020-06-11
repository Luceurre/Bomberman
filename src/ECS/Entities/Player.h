//
// Created by pglandon on 6/9/20.
//

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "../Components/Components.h"

#define TEX_PATH "assets/orc.png"

enum PlayerState {
    IDLE
};

inline Entity* makePlayer(Manager& manager) {
    auto& entity(manager.addEntity());

    int posX[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int posY[9] = {8, 8, 8, 8, 8, 8, 8, 8, 8};
    int ticks[9] = {20, 20, 20, 20, 20, 20, 20, 20, 20};

    auto animUP = AnimationComponent(TEX_PATH, 64, 64, posX, posY, ticks, 9);

    // entity.addComponents<AnimationComponent>(TEX_PATH, 32, 32, posX, posY, ticks, 4);

    State arg1[1] = {IDLE};
    AnimationComponent arg2[1] = {animUP};
    int arg3 = 1;
    State arg4 = IDLE;

    entity.addComponents<MultiAnimationComponent>(arg1, arg2, arg3, arg4);

    return &entity;
}


#endif //BOMBERMAN_PLAYER_H
