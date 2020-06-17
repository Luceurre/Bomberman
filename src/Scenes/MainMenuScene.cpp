//
// Created by pglandon on 5/31/20.
//

#include "MainMenuScene.h"
#include "../ECS/Entities/Background.h"
#include "../ECS/Entities/Button.h"

int MainMenuScene::initialize() {
    GraphicScene::initialize();

    // On crée les boutons et se genre de trucs
    background = makeBackground(manager, sceneWindow->renderer);

    auto callback = new Functor0<void>(this, &MainMenuScene::launch_new_game);
    auto callback2 = new Functor0<void>(this, &MainMenuScene::addPlayer);
    auto callback3 = new Functor0<void>(this, &MainMenuScene::removePlayer);

            makeButton(manager, (704 - 400) / 2, 300, "assets/play_button.png", callback);
    auto button_prev = makeButton(manager, 104, 500, "assets/button_prev.png", callback3);
    auto button_next = makeButton(manager, 500, 500, "assets/button_next.png", callback2);
    button_prev->getComponent<HitboxComponent>().width = 100;
    button_prev->getComponent<HitboxComponent>().height = 100;
    button_next->getComponent<HitboxComponent>().width = 100;
    button_next->getComponent<HitboxComponent>().height = 100;


    numeric_font = TTF_OpenFont("assets/fonts/font_numeric.ttf", 4096);

    for (int i = 0; i < 5; i++) {
        auto surf = TTF_RenderText_Solid(numeric_font, to_string(i).c_str(), SDL_Color{0, 0, 0, 255});
        player_count_tex[i] = SDL_CreateTextureFromSurface(sceneWindow->renderer, surf);
    }

    set_model_refresh_rate(100);


    player_count = 4;

    return 0;
}

int MainMenuScene::model() {

    manager.update();


    return 0;
}

int MainMenuScene::view() {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        manager.spreadEvent(event);
    }

    SDL_RenderClear(sceneWindow->renderer);
    manager.draw();

    auto rect = SDL_Rect{(704 - 100) / 2, 500, 100, 100};
    SDL_RenderCopy(sceneWindow->renderer, player_count_tex[player_count], nullptr, &rect);

    SDL_RenderPresent(sceneWindow->renderer);

    return 0;
}
