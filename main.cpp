#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "src/Scenes/Scene.h"
#include "src/Scenes/LoadingScene.h"
#include "src/Managers/SceneManager.h"

void launch() {
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

    // Closing log file for sanity
    Logger::closeLogFile();
}

class A {
public:

    inline A() {
        order = 0;
    }

    int order;

    inline friend bool operator<(const A& right, const A& left) {
        return right.order < left.order;
    }

    std::string print() {
        return std::to_string(order);
    }
};

void test() {
    A a1, a2;
    a1.order = 5;
    a2.order = 8;

    std::vector<A> test;

    // std::make_heap(test.begin(), test.end());

    test.push_back(a1);
    std::push_heap(test.begin(), test.end());
    test.push_back(a2);
    std::push_heap(test.begin(), test.end());

    for (auto t : test) {
        std::cout << t.print() << std::endl;
    }



    if (a2 < a1) {
        std::cout << "Hey" << std::endl;
    }
}

int main() {
    launch();

    return 0;
}
