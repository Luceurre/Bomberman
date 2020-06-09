//
// Created by pglandon on 6/1/20.
//

#ifndef BOMBERMAN_BASICSPRITECOMPONENT_H
#define BOMBERMAN_BASICSPRITECOMPONENT_H

// The most basic form of drawable component
// doesn't handle different size of screen, animation, ...
// just draw itself at the desired location (+ reload texture on  changed display size).
// Should be used to draw background for example, using default SDL upscaling method.

// TODO : Auto texture reloading -> waiting for event system.
class BasicSpriteComponent : public Component {
public:
            // pas fan de ça, mais pas le temps de faire mieux....
            SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SDL_Renderer* renderer;

    inline BasicSpriteComponent() {
        texture = nullptr;
    }

    inline BasicSpriteComponent(SDL_Texture* tex) {
        texture = tex;
    }

    inline BasicSpriteComponent(std::string tex_path) {
        texture = TextureManager::LoadTexture(tex_path, srcRect);
    }

    inline ~BasicSpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    inline void init() override {
        if(!entity->hasComponent<PositionComponent>()) {
            entity->addComponents<PositionComponent>();
            warn("Using default PositionComponent.");
        }
    }

    inline void draw() override {

        TextureManager::DrawFullscreen(texture);
    }

};


#endif //BOMBERMAN_BASICSPRITECOMPONENT_H
