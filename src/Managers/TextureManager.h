//
// Created by julien on 18/04/2020.
//
#pragma once
#ifndef ATELIERPROG_TEXTUREMANAGER_H
#define ATELIERPROG_TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "../Utils//Logger.h"

// Gros tu peux pas faire ça!
// Comment je fais pour utiliser ton code dans mon programme maintenant ????
// bah je peux pas c'est ça la réponse...
class TextureManager : protected Logger {
private:
    static std::map<std::string, SDL_Surface *> textures;
public:
    static SDL_Renderer* renderer;
    static SDL_Texture* LoadTexture(const std::string& fileName, SDL_Rect &texture_dimension);
    static void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip);
    static void DrawFullTex(SDL_Texture* tex, int x, int y, int w, int h);
    static void DrawFullTex(SDL_Texture* tex, SDL_Rect* destRect);
    // Draw fullscreen for the current renderer's viewport
    static void DrawFullscreen(SDL_Texture* tex);
};



#endif //ATELIERPROG_TEXTUREMANAGER_H
