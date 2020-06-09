//
// Created by pglandon on 5/31/20.
//

#include "MainMenuScene.h"
#include "../ECS/Entities/Background.h"
#include "../ECS/Entities/Button.h"

int MainMenuScene::initialize() {
    GraphicScene::initialize();

    // On crée les boutons et se genre de trucs
    // background = makeBackground(manager, sceneWindow->renderer, "assets/background/test.png");

    auto callback = new Functor0<void>(this, &MainMenuScene::launch_new_game);
    makeButton(manager, 0, 0, "assets/buttons/7.png", callback);

    set_model_refresh_rate(250);

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


    SDL_RenderPresent(sceneWindow->renderer);

    return 0;
}
