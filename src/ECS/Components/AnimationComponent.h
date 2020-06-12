//
// Created by pglandon on 6/9/20.
//

#ifndef BOMBERMAN_ANIMATIONCOMPONENT_H
#define BOMBERMAN_ANIMATIONCOMPONENT_H


#include <vector>

#include "Components.h"

using namespace std;

// TODO : lock currentSprite!

class AnimationComponent : public AdvancedSpriteComponent {
protected:
    vector<int> ticksPerAnimation;
    vector<SDL_Rect> subspritesPos;
    // Not the good way to do it, we load the entire texture, and then we clip the requested part instead of
    // creating
    int currentSprite;
    int currentSpriteTickCount;
    int spritesCount;
    int animWidth;
    int animHeight;
public:
    inline AnimationComponent(string tex_path, int spriteWidth, int spriteHeight,
            int* spritePosX, int* spritePosY, int* ticks, int sprites_count) : AdvancedSpriteComponent(tex_path) {
        for(int i = 0; i < sprites_count; i++) {
            subspritesPos.push_back(SDL_Rect{spriteWidth * spritePosX[i], spriteHeight * spritePosY[i],
                    spriteWidth, spriteHeight});
            ticksPerAnimation.push_back(ticks[i]);
        }
        currentSprite = 0;
        spritesCount = sprites_count;
        animWidth = spriteWidth;
        animHeight = spriteHeight;
    }

    inline void init() override {
        AdvancedSpriteComponent::init();
    }

    inline void update() override {
        hitboxComponent->width = animWidth;
        hitboxComponent->height = animHeight;

        AdvancedSpriteComponent::update();

        if (currentSpriteTickCount > ticksPerAnimation[currentSprite]) {
            currentSpriteTickCount = 0;
            currentSprite = (currentSprite + 1) % spritesCount;
            srcRect = subspritesPos[currentSprite];
        }
        currentSpriteTickCount++;
    }
};


#endif //BOMBERMAN_ANIMATIONCOMPONENT_H
