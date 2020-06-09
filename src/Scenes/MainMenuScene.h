//
// Created by pglandon on 5/31/20.
//

#ifndef ATELIERPROG_MAINMENUSCENE_H
#define ATELIERPROG_MAINMENUSCENE_H

#include <string>

#include "GraphicScene.h"
#include "../ECS/ECS.h"
#include "../Managers/SceneManager.h"
#include "GameScene.h"


class MainMenuScene : public GraphicScene {
protected:
    inline std::string descriptor() override {
        return "(MainMenuScene)";
    }

    int model() override;
    int view() override;

    int selected_button;
    Manager manager;
    Entity* background;
    Entity* puteButton;
public:
    inline MainMenuScene() : GraphicScene() {}
    int initialize() override;
    inline void launch_new_game() {
        set_state(STOPPED);

        auto sceneManager = SceneManager::getInstance();

        auto gameScene = new GameScene();
        gameScene->initialize();

        sceneManager->add_scene(gameScene);
    }
};




#endif //ATELIERPROG_MAINMENUSCENE_H
