//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_SPRITEREPEATCOMPONENT_H
#define BOMBERMAN_SPRITEREPEATCOMPONENT_H

#include "Components.h"

class SpriteRepeatComponent : public BasicSpriteComponent {
public:

    inline SpriteRepeatComponent(std::string tex_path) : BasicSpriteComponent(tex_path) {

    }

    inline void draw() override {

        TextureManager::DrawFullscreenRepeat(texture, srcRect);
    }
};


#endif //BOMBERMAN_SPRITEREPEATCOMPONENT_H
