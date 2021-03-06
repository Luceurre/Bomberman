#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "src/Scenes/Scene.h"
#include "src/Scenes/LoadingScene.h"
#include "src/Managers/SceneManager.h"
#include "src/Managers/EventManager.h"

// ou comment avoir de magnifique fuite de mémoire...
void killEverything(Event* e) {
    std::cout << "Goodbye!" << std::endl;
    exit(0);
}


void launch() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Couldn't initialize SDL!" << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "Coudln't initialize TTF!" << std::endl;
        exit(1);
    }

    // On enregistre le callback pour la fermeture du programme.
    auto eventManager = EventManager::getInstance();
    SDL_Event closeEventSDL{};
    closeEventSDL.type = SDL_QUIT;
    SDLEvent closeEvent(closeEventSDL);
    closeEvent.eventType = EventTypeManager::WindowClose;
    eventManager->AddEventSubject(closeEvent, &killEverything);

    // On crée la première scène
    Scene* loadingScene = new LoadingScene();
    loadingScene->initialize();

    // On l'envoie dans le SceneManager
    SceneManager* sceneManager = SceneManager::getInstance();
    sceneManager->add_scene(loadingScene);
//
//    while (!sceneManager->isEmpty()) {
//        int i = (int)sceneManager->scenes.size() - 1;
//        while (i >= 0) {
//            sceneManager->scenes[i]->run();
//            if (sceneManager->scenes[i]->get_state() == STOPPED) {
//                // sceneManager->scenes[i]->quit();
//                delete sceneManager->scenes[i];
//                sceneManager->scenes.erase(sceneManager->scenes.begin() + i);
//            }
//            i--;
//        }
//    }

    while (!sceneManager->isEmpty()) {
        auto it = sceneManager->scenes.top();
        sceneManager->scenes.pop();

        it->run();

        if (it->get_state() == STOPPED) {
            it->quit();
            delete it;
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

int main(int argc, char** argv) {
    launch();

    return 0;
}
