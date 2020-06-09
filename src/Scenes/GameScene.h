//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_GAMESCENE_H
#define BOMBERMAN_GAMESCENE_H


#include "GraphicScene.h"
#include "../ECS/ECS.h"
#include "../ECS/Entities/FloorTile.h"

class GameScene : public GraphicScene {
protected:
    inline std::string descriptor() override {
        return "(GameScene)";
    }

    Manager manager;
public:

    inline int initialize() override {
        GraphicScene::initialize();
        makeFloorTile(manager);

        return 0;
    }

    inline int view() override {
        SDL_RenderClear(sceneWindow->renderer);
        manager.draw();


        SDL_RenderPresent(sceneWindow->renderer);

        return 0;
    }
};


#endif //BOMBERMAN_GAMESCENE_H
