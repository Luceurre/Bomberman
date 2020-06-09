//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_GAMESCENE_H
#define BOMBERMAN_GAMESCENE_H


#include "GraphicScene.h"
#include "../ECS/ECS.h"
#include "../ECS/Entities/FloorTile.h"
#include "../ECS/Entities/Background.h"
#include "../ECS/Entities/Player.h"

class GameScene : public GraphicScene {
protected:
    inline std::string descriptor() override {
        return "(GameScene)";
    }

    Manager manager;
public:

    inline int initialize() override {
        GraphicScene::initialize();
        // makeFloorTile(manager);
        //makeBackground(manager, nullptr, "assets/background/test.png");
        makePlayer(manager);
        set_model_refresh_rate(250);
        set_fps(UNCAPPED);

        return 0;
    }

    inline int model() override {
        manager.update();

        return 0;
    }

    inline int view() override {

        SDL_SetRenderDrawColor(sceneWindow->renderer, 255, 0, 255, 255);
        SDL_RenderClear(sceneWindow->renderer);
        manager.draw();


        SDL_RenderPresent(sceneWindow->renderer);

        return 0;
    }
};


#endif //BOMBERMAN_GAMESCENE_H
