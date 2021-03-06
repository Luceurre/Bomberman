//
// Created by pglandon on 6/11/20.
//

#ifndef BOMBERMAN_ADVANCEDSPRITECOMPONENT_H
#define BOMBERMAN_ADVANCEDSPRITECOMPONENT_H

#include "Components.h"

class AdvancedSpriteComponent : public SpriteComponent {
public:
    SDL_Rect srcRect;
    bool shouldDraw = true;

    inline AdvancedSpriteComponent(std::string tex_path) : SpriteComponent(tex_path) {

    }

    inline void draw() override {
        if (shouldDraw)
            TextureManager::Draw(texture, &srcRect, &destRect);
    }

};


#endif //BOMBERMAN_ADVANCEDSPRITECOMPONENT_H
