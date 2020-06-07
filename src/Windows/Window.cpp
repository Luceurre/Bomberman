//
// Created by pglan on 20/04/2020.
//

#include "Window.h"
//
//Window::Window(int x, int y, int w, int h, Uint32 sdl_flags) {
//    this->x = x;
//    this->y = y;
//    this->w = w;
//    this->h = h;
//    this->sdl_flags = sdl_flags;
//}

Window createDefaultWindow() {
    Window w;

    SDL_CreateWindowAndRenderer(1080, 720, 0, &w.window, &w.renderer);
    return w;
}