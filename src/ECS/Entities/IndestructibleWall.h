//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_INDESTRUCTIBLEWALL_H
#define BOMBERMAN_INDESTRUCTIBLEWALL_H

#include "../Components/Components.h"
#include "../Groups/Groups.h"

#define WALL_TEX_PATH "assets/wall.png"

inline Entity* makeIndestructibleWall(Manager& manager, int x, int y) {
    auto& wall = manager.addEntity();

    wall.addComponents<PositionComponent>(x, y);
    wall.addComponents<SpriteComponent>(WALL_TEX_PATH);
    wall.addComponents<BlockComponent>(false);

    manager.AddToGroup(&wall, PLAYER_BLOCK);

    return &wall;
}

#endif //BOMBERMAN_INDESTRUCTIBLEWALL_H