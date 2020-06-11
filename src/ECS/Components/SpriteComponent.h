//
// Created by pglandon on 6/7/20.
//

#ifndef BOMBERMAN_SPRITECOMPONENT_H
#define BOMBERMAN_SPRITECOMPONENT_H


#include "Components.h"
#include "../../Managers/TextureManager.h"

// Permet d'afficher les images à l'écran avec un peu plus d'option!
// comportement de base: la hitbox est set à la taille de l'image chargée.
class SpriteComponent : public Component {
public:
    SDL_Texture *texture;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SDL_Rect destRect;
    HitboxComponent* hitboxComponent;
    std::string texPath;

    inline SpriteComponent() {
        texture = nullptr;
        hitboxComponent = nullptr;
    }

    inline SpriteComponent(std::string tex_path) : SpriteComponent() {
        texPath = tex_path;
    }


    inline ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    inline void init() override {
        texture = TextureManager::LoadTexture(texPath, destRect);

        if(!entity->hasComponent<HitboxComponent>()) {
            entity->addComponents<HitboxComponent>();
            warn("Using default Hitbox.");
        }

        hitboxComponent = &entity->getComponent<HitboxComponent>();
        hitboxComponent->width = destRect.w;
        hitboxComponent->height = destRect.h;
    }

    inline void update() override {
        destRect = {hitboxComponent->positionComponent->posX,
                    hitboxComponent->positionComponent->posY,
                    hitboxComponent->width,
                    hitboxComponent->height};
    }

    inline void draw() override {
        TextureManager::DrawFullTex(texture, &destRect);
    }
};


#endif //BOMBERMAN_SPRITECOMPONENT_H
