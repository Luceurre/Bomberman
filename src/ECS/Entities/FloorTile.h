//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_FLOORTILE_H
#define BOMBERMAN_FLOORTILE_H

#include "../ECS.h"
#include "../Components/Components.h"

#define FLOOR_TILE_TEX_PATH "assets/buttons/7.png"

inline Entity* makeFloorTile(Manager& manager) {
    auto& entity(manager.addEntity());
    entity.addComponents<SpriteRepeatComponent>(FLOOR_TILE_TEX_PATH);

    return &entity;
}



#endif //BOMBERMAN_FLOORTILE_H
