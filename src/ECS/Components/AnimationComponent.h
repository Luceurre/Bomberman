//
// Created by pglandon on 6/9/20.
//

#ifndef BOMBERMAN_ANIMATIONCOMPONENT_H
#define BOMBERMAN_ANIMATIONCOMPONENT_H


#include <vector>

#include "Components.h"

using namespace std;

class AnimationComponent : public Component {
protected:
    vector<int> ticksPerAnimation;
    vector<SDL_Rect> subspritesPos;
    // Not the good way to do it, we load the entire texture, and then we clip the requested part instead of
    // creating
    SDL_Texture* sprites;
    string texPath;
    int currentSprite;
    int currentSpriteTickCount;
    int spritesCount;
    int width;
    int height;
public:
    HitboxComponent* hitboxComponent;

    inline AnimationComponent(string tex_path, int spriteWidth, int spriteHeight,
            int* spritePosX, int* spritePosY, int* ticks, int sprites_count) {
        for(int i = 0; i < sprites_count; i++) {
            subspritesPos.push_back(SDL_Rect{spriteWidth * spritePosX[i], spriteHeight * spritePosY[i],
                    spriteWidth, spriteHeight});
            ticksPerAnimation.push_back(ticks[i]);
        }
        texPath = tex_path;
        currentSprite = 0;
        spritesCount = sprites_count;
        width = spriteWidth;
        height = spriteHeight;
    }

    inline void init() override {
        SDL_Rect destRect;

        sprites = TextureManager::LoadTexture(texPath, destRect);

        if(!entity->hasComponent<HitboxComponent>()) {
            entity->addComponents<HitboxComponent>();
            warn("Using default Hitbox.");
        }

        hitboxComponent = &entity->getComponent<HitboxComponent>();
        hitboxComponent->width = width;
        hitboxComponent->height = height;
    }

    inline void update() override {
        if (currentSpriteTickCount > ticksPerAnimation[currentSprite]) {
            currentSpriteTickCount = 0;
            currentSprite = (currentSprite + 1) % spritesCount;
        }
        currentSpriteTickCount++;
    }

    inline void draw() override {
        SDL_Rect destRect = {hitboxComponent->positionComponent->posX,
                             hitboxComponent->positionComponent->posY,
                             hitboxComponent->width,
                             hitboxComponent->height};
        TextureManager::Draw(sprites, &subspritesPos[currentSprite], &destRect);
    }
};


#endif //BOMBERMAN_ANIMATIONCOMPONENT_H
