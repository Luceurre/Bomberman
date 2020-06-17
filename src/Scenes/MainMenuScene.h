//
// Created by pglandon on 5/31/20.
//

#ifndef ATELIERPROG_MAINMENUSCENE_H
#define ATELIERPROG_MAINMENUSCENE_H

#include <string>
#include <SDL_ttf.h>

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

    int player_count;
    SDL_Texture* player_count_tex[5];

    TTF_Font* numeric_font;
public:
    inline MainMenuScene() : GraphicScene() {
        player_count = 2;
    }
    int initialize() override;
    inline void launch_new_game() {
        set_state(STOPPED);

        auto sceneManager = SceneManager::getInstance();

        auto gameScene = new GameScene(player_count);
        gameScene->initialize();

        sceneManager->add_scene(gameScene);
    }

    inline void addPlayer() {
        info("adding player...");
        if (player_count < 4)
            player_count++;
    }

    inline void removePlayer() {
        info("removing player...");
        if (player_count > 2)
            player_count--;
    }
};




#endif //ATELIERPROG_MAINMENUSCENE_H
