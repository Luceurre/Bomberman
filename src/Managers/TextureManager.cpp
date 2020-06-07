//
// Created by julien on 18/04/2020.
//

#include "TextureManager.h"
#include "../Utils/Logger.h"

std::map<std::string, SDL_Surface *> TextureManager::textures;

SDL_Renderer* TextureManager::renderer = nullptr;

SDL_Texture* TextureManager::LoadTexture(const std::string& fileName, SDL_Rect &texture_dimension) {
    if (!TextureManager::renderer) {
        static_log(ERROR, "Initialize renderer first!");
        return nullptr;
    }

    auto texture = TextureManager::textures.find(fileName);
    SDL_Surface* tempSurface;

    // Si on l'a pas déjà chargé, on la load
    if (texture == TextureManager::textures.end()) {
        tempSurface = IMG_Load(fileName.c_str());
        // Static log here maybe ?
        if (!tempSurface) {
            static_log(FATAL, "Couldn't load texture : " + fileName);
            exit(-1);
        } else {
            static_log(INFO, "Added texture : " + fileName);
            TextureManager::textures.emplace(fileName, tempSurface);
        }
    }

    tempSurface = TextureManager::textures.at(fileName);

    texture_dimension.w = tempSurface->w;
    texture_dimension.h = tempSurface->h;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(TextureManager::renderer, tempSurface);

    if (!tex) {
        static_log(ERROR, "Couldn't create texture!");
    }

    // TODO : free all textures at the end of the program
    // SDL_FreeSurface(tempSurface);

    return tex;

}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip) {
    // SDL_RenderCopyEx(TextureManager::renderer, tex, &src, &dest, 0, NULL, flip);
    SDL_RenderCopy(renderer, tex, src, dest);
}

void TextureManager::DrawFullscreen(SDL_Texture *tex) {
    SDL_Rect dest;
    SDL_RenderGetViewport(renderer, &dest);


    SDL_RenderCopy(renderer, tex, nullptr, &dest);
}

void TextureManager::DrawFullTex(SDL_Texture *tex, SDL_Rect* destRect) {
    SDL_RenderCopy(renderer, tex, nullptr, destRect);
}

void TextureManager::DrawFullTex(SDL_Texture *tex, int x, int y, int w, int h) {
    SDL_Rect destRect = {x, y, w, h};
    DrawFullTex(tex, &destRect);
}
