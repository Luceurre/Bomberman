//
// Created by pglandon on 6/13/20.
//

#ifndef BOMBERMAN_DIRECTION_H
#define BOMBERMAN_DIRECTION_H

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

inline int DIRECTION[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

#endif //BOMBERMAN_DIRECTION_H
