//
// Created by pglandon on 6/11/20.
//

#ifndef BOMBERMAN_MULTIANIMATIONCOMPONENT_H
#define BOMBERMAN_MULTIANIMATIONCOMPONENT_H

#include "Components.h"

using namespace std;

typedef int State;


// Handle multiple animations Components for a given entity.
class MultiAnimationComponent : public Component {
protected:
    map<State, AnimationComponent> animations;
    State currentState;

public:
    inline MultiAnimationComponent(State* states, AnimationComponent* anims, int animCount, State defaultState) {
        for(int i = 0; i < animCount; ++i) {
            if(states[i] != defaultState)
                anims[i].active = false;
            animations.emplace(states[i], anims[i]);
        }
        currentState = defaultState;
    }

    inline void init() override {
        for(auto& it : animations) {
            entity->addComponents<AnimationComponent>(it.second);
        }
    }

    inline void setState(State newState) {
        auto it = animations.find(currentState);
        if (it != animations.end()) {
            it->second.active = false;
        }

        currentState = newState;

        it = animations.find(currentState);
        if (it != animations.end()) {
            it->second.active = true;
        } else {
            warn("State not found!");
        }
    }
};


#endif //BOMBERMAN_MULTIANIMATIONCOMPONENT_H
