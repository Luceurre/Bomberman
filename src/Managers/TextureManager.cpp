//
// Created by julien on 18/04/2020.
//

#include "TextureManager.h"
#include "../Utils/Logger.h"

std::map<std::string, SDL_Surface *> TextureManager::surfaces;
std::map<std::string, SDL_Texture *> TextureManager::textures;

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
            TextureManager::surfaces.emplace(fileName, tempSurface);
            TextureManager::textures.emplace(fileName, SDL_CreateTextureFromSurface(TextureManager::renderer, tempSurface));
        }
    }

    tempSurface = TextureManager::surfaces.at(fileName);

    texture_dimension.w = tempSurface->w;
    texture_dimension.h = tempSurface->h;

    // TODO : free all surfaces at the end of the program

    return TextureManager::textures.at(fileName);
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect* src, SDL_Rect* dest) {
    // SDL_RenderCopyEx(TextureManager::renderer, tex, &src, &dest, 0, NULL, flip);
    SDL_RenderCopy(renderer, tex, src, dest);
}

void TextureManager::DrawFullscreen(SDL_Texture *tex) {
    SDL_Rect dest;
    SDL_RenderGetViewport(renderer, &dest);


    SDL_RenderCopy(renderer, tex, nullptr, &dest);
}

void TextureManager::DrawFullscreenRepeat(SDL_Texture *tex, const SDL_Rect& tex_dim) {
    SDL_Rect viewport;
    SDL_RenderGetViewport(renderer, &viewport);

    SDL_Rect dest;
    int i = 0, j = 0;

    while ((i - 1) * tex_dim.w < viewport.w) {
        j = 0;

        while ((j - 1) * tex_dim.h < viewport.h) {
            dest = {tex_dim.w * i, tex_dim.h * j, tex_dim.w, tex_dim.h};
            SDL_RenderCopy(renderer, tex, nullptr, &dest);
            j++;
        }
        i++;
    }
}

void TextureManager::DrawFullTex(SDL_Texture *tex, SDL_Rect* destRect) {
    SDL_RenderCopy(renderer, tex, nullptr, destRect);
}

void TextureManager::DrawFullTex(SDL_Texture *tex, int x, int y, int w, int h) {
    SDL_Rect destRect = {x, y, w, h};
    DrawFullTex(tex, &destRect);
}

SDL_Surface *TextureManager::LoadSurface(const std::string &fileName, SDL_Rect &surface_dimension) {
    if (!TextureManager::renderer) {
        static_log(ERROR, "Initialize renderer first!");
        return nullptr;
    }

    auto texture = TextureManager::surfaces.find(fileName);
    SDL_Surface* tempSurface;

    // Si on l'a pas déjà chargé, on la load
    if (texture == TextureManager::surfaces.end()) {
        tempSurface = IMG_Load(fileName.c_str());
        // Static log here maybe ?
        if (!tempSurface) {
            static_log(FATAL, "Couldn't load texture : " + fileName);
            exit(-1);
        } else {
            static_log(INFO, "Added texture : " + fileName);
            TextureManager::surfaces.emplace(fileName, tempSurface);
        }
    }

    tempSurface = TextureManager::surfaces.at(fileName);

    surface_dimension.w = tempSurface->w;
    surface_dimension.h = tempSurface->h;

    return tempSurface;
}
