//
// Created by julien on 21/04/2020.
//

#include "ECS.h"

void Entity::addGroup(Group mGroup) {
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}