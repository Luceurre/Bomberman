//
// Created by pglandon on 5/31/20.
//

#include "LoadingScene.h"
#include "../Managers//WindowManager.h"
#include "MainMenuScene.h"
#include "../Managers/SceneManager.h"

int LoadingScene::initialize() {
    Scene::initialize();

    // On charge les options ici relatives à  la fenêtre ici!
    int width = 1080;
    int height = 1080;
    Uint32 flags = 0;
    Uint32 rendFlags = SDL_RENDERER_ACCELERATED;
    int vsync = true;
    bool fullscreen = false;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (vsync)
        flags |= SDL_RENDERER_PRESENTVSYNC;

    auto* gameWindow = new Window{nullptr, nullptr};
    // On crée la fenêtre et le renderer
    gameWindow->window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    gameWindow->renderer = SDL_CreateRenderer(gameWindow->window, -1, rendFlags);

    // On l'enregistre pour les autres scènes :
    WindowManager::getInstance().add_primary_window(gameWindow);

    sceneWindow = gameWindow;

    return 0;
}

int LoadingScene::model() {
    // On charge tous les assets pendant que view() se charge d'afficher un joli loading screen.

    // Une fois fini, on lance la scene suivante ici ? depuis quit() ?
    set_state(STOPPED);

    return 0;
}

int LoadingScene::quit() {
    Scene* mainMenu = new MainMenuScene();
    mainMenu->initialize();

    SceneManager::getInstance()->add_scene(mainMenu);
    set_state(DESTROYED);

    return 0;
}
