//
// Created by pglandon on 5/31/20.
//

#include "MainMenuScene.h"
#include "../ECS/Entities/Background.h"

int MainMenuScene::initialize() {
    GraphicScene::initialize();

    // On crée les boutons et se genre de trucs
    background = makeBackground(manager, sceneWindow->renderer, "assets/background/test.png");

    return 0;
}

int MainMenuScene::model() {


    manager.update();


    return 0;
}

int MainMenuScene::view() {

    SDL_RenderClear(sceneWindow->renderer);
    manager.draw();


    SDL_RenderPresent(sceneWindow->renderer);

    return 0;
}
