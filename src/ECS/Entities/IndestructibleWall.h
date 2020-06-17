//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_INDESTRUCTIBLEWALL_H
#define BOMBERMAN_INDESTRUCTIBLEWALL_H

#include "../Components/Components.h"
#include "../Groups/Groups.h"

#define WALL_TEX_PATH "assets/wall.png"

inline Entity* makeIndestructibleWall(Manager& manager, int x, int y) {
    auto& wall = manager.addEntity(70);

    wall.addComponents<PositionComponent>(x, y);
    wall.addComponents<TrueHitboxComponent>(64, 64);
    wall.addComponents<HitboxComponent>(64, 64);
    wall.addComponents<SpriteComponent>(WALL_TEX_PATH);
    wall.addComponents<BlockComponent>(new BlockBehaviourWallComponent);

    manager.AddToGroup(&wall, PLAYER_BLOCK);

    return &wall;
}

inline void makeBorderIndestructibleWall(Manager& manager) {
    for (int i = 0; i < 11; ++i) {
        makeIndestructibleWall(manager, i * 64, 0);
    }

    for (int i = 0; i < 11; ++i) {
        makeIndestructibleWall(manager, i * 64, 704 - 64);
    }

    for (int i = 1; i < 10; ++i) {
        makeIndestructibleWall(manager, 0, i * 64);
    }

    for (int i = 1; i < 10; ++i) {
        makeIndestructibleWall(manager, 704 - 64, i * 64);
    }

    for (int i = 2; i < 9; i+=2) {
        for (int j = 2; j < 9; j+=2) {
            makeIndestructibleWall(manager, 64 * i, 64 * j);
        }
    }
}

#endif //BOMBERMAN_INDESTRUCTIBLEWALL_H