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
    bool repeat;
    // permet de synchroniser view et model!
    cb::Callback0<void> fallback;
public:
    inline AnimationComponent(const string& tex_path, const int spriteWidth, const int spriteHeight,
            const int* spritePosX, const int* spritePosY, const int* ticks, const int sprites_count,
            bool shouldRepeat = true, const cb::Callback0<void> endfallback = cb::Callback0<void>{}) : AdvancedSpriteComponent(tex_path) {
        for(int i = 0; i < sprites_count; i++) {
            subspritesPos.push_back(SDL_Rect{spriteWidth * spritePosX[i], spriteHeight * spritePosY[i],
                    spriteWidth, spriteHeight});
            ticksPerAnimation.push_back(ticks[i]);
        }
        currentSprite = 0;
        spritesCount = sprites_count;
        animWidth = spriteWidth;
        animHeight = spriteHeight;
        repeat = shouldRepeat;
        fallback = endfallback;
        currentSpriteTickCount = 0;
    }

    inline void init() override {
        AdvancedSpriteComponent::init();

        hitboxComponent->width = animWidth;
        hitboxComponent->height = animHeight;
    }

    inline void update() override {
        AdvancedSpriteComponent::update();

        if (repeat) {
            if (currentSpriteTickCount > ticksPerAnimation[currentSprite]) {
                currentSpriteTickCount = 0;
                currentSprite = (currentSprite + 1) % spritesCount;
                srcRect = subspritesPos[currentSprite];
            }
            currentSpriteTickCount++;
        } else {
            if (currentSpriteTickCount > ticksPerAnimation[currentSprite]) {
                currentSpriteTickCount = 0;
                currentSprite = (currentSprite + 1);
                srcRect = subspritesPos[currentSprite];
            }
            currentSpriteTickCount++;
            if (currentSprite >= spritesCount)
                fallback();
        }

    }
};


#endif //BOMBERMAN_ANIMATIONCOMPONENT_H
