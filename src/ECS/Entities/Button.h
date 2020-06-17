//
// Created by pglandon on 6/7/20.
//

#ifndef BOMBERMAN_BUTTON_H
#define BOMBERMAN_BUTTON_H


#include "../../Utils/Functor.h"
#include "../Components/Components.h"

inline Entity* makeButton(Manager& manager, int x, int y, std::string texPath, Functor0<void>* callback) {
    auto& entity(manager.addEntity(10));
    entity.addComponents<PositionComponent>(x, y);
    entity.addComponents<SpriteComponent>(texPath);
    entity.addComponents<ClickableComponent>(callback);

    return &entity;
}


#endif //BOMBERMAN_BUTTON_H
