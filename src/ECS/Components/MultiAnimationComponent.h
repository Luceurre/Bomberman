//
// Created by pglandon on 6/11/20.
//

#ifndef BOMBERMAN_MULTIANIMATIONCOMPONENT_H
#define BOMBERMAN_MULTIANIMATIONCOMPONENT_H

#include "Components.h"

using namespace std;

typedef int State;

struct StatedAnimation {
    AnimationComponent anim;
    State state;
};

// Handle multiple animations Components for a given entity.
class MultiAnimationComponent : public Component {
protected:
    map<State, AnimationComponent> animationsToInit;
    map<State, AnimationComponent*> animations;
    State currentState;

    inline string descriptor() override {
        return "(MultiAnimation)";
    };

public:
    inline MultiAnimationComponent(State* states, AnimationComponent* anims, int animCount, State defaultState) {
        for(int i = 0; i < animCount; ++i) {
            animationsToInit.emplace(states[i], anims[i]);
        }
        currentState = defaultState;
    }

    inline MultiAnimationComponent(vector<StatedAnimation> stated_animation, State defaultState) {
        for(auto& it : stated_animation) {
            animationsToInit.emplace(it.state, it.anim);
        }

        currentState = defaultState;
    }

    inline void init() override {
        for(auto& it : animationsToInit) {
            if (it.first != currentState)
                it.second.shouldDraw = false;
            entity->addComponents<AnimationComponent>(it.second);
            animations.insert(pair<State, AnimationComponent*>(it.first, &entity->getComponent<AnimationComponent>()));
        }
    }

    inline void setState(State newState) {
        auto it = animations.find(currentState);
        if (it != animations.end()) {
            it->second->shouldDraw = false;
        }

        currentState = newState;

        it = animations.find(currentState);
        if (it != animations.end()) {
            it->second->shouldDraw = true;
        } else {
            warn("State not found!");
        }
    }
};


#endif //BOMBERMAN_MULTIANIMATIONCOMPONENT_H
