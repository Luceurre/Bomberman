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
#include "../Events/Event.h"
#include "../Managers/EventManager.h"

class GameScene : public GraphicScene {
protected:
    inline std::string descriptor() override {
        return "(GameScene)";
    }

    Manager manager;
    EventManager* eventManager;
    Player* player1;
public:

    inline int initialize() override {
        GraphicScene::initialize();
        // makeFloorTile(manager);
        //makeBackground(manager, nullptr, "assets/background/test.png");
        player1 = makePlayer(manager);

        set_model_refresh_rate(250);
        set_fps(UNCAPPED);

        eventManager = EventManager::getInstance();

        return 0;
    }

    inline int model() override {
        manager.update();

        eventManager->dispatchQueue();

        return 0;
    }

    inline int view() override {

        SDL_Event e;

        // C'est pas comme ça que je voulais faire, mais plus le temps donc tant pis....

        while(SDL_PollEvent(&e)) {
            auto eventSDL = new SDLEvent(e);
            if (e.type == SDL_QUIT)
                eventSDL->eventType = EventTypeManager::WindowClose;
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_z:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, UP, false});
                        break;
                    case SDLK_s:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, DOWN, false});
                        break;
                    case SDLK_q:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, LEFT, false});
                        break;
                    case SDLK_d:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, RIGHT, false});
                        break;
                    default:
                        break;
                }
            }

            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_z:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, UP, true});
                        break;
                    case SDLK_s:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, DOWN, true});
                        break;
                    case SDLK_q:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, LEFT, true});
                        break;
                    case SDLK_d:
                        eventManager->push_event(new Player::PlayerMoveEvent{0, RIGHT, true});
                        break;
                    default:
                        break;
                }
            }

            eventManager->push_event(eventSDL);
        }

        SDL_SetRenderDrawColor(sceneWindow->renderer, 255, 0, 255, 255);
        SDL_RenderClear(sceneWindow->renderer);
        manager.draw();


        SDL_RenderPresent(sceneWindow->renderer);

        return 0;
    }
};


#endif //BOMBERMAN_GAMESCENE_H
