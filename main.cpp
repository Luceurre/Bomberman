#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "src/Scenes/Scene.h"
#include "src/Scenes/LoadingScene.h"
#include "src/Managers/SceneManager.h"

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Couldn't initialize SDL!" << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "Coudln't initialize TTF!" << std::endl;
        exit(1);
    }

    // On crée la première scène
    Scene* loadingScene = new LoadingScene();
    loadingScene->initialize();

    // On l'envoie dans le SceneManager
    SceneManager* sceneManager = SceneManager::getInstance();
    sceneManager->add_scene(loadingScene);

    while (!sceneManager->isEmpty()) {
        int i = (int)sceneManager->scenes.size() - 1;
        while (i >= 0) {
            sceneManager->scenes[i]->run();
            if (sceneManager->scenes[i]->get_state() == STOPPED) {
                // sceneManager->scenes[i]->quit();
                delete sceneManager->scenes[i];
                sceneManager->scenes.erase(sceneManager->scenes.begin() + i);
            }
            i--;
        }
    }

}
