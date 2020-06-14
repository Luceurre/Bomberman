//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_GAMESCENE_H
#define BOMBERMAN_GAMESCENE_H


#include "GraphicScene.h"
#include "../ECS/ECS.h"
#include "../ECS/Entities/Entities.h"
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
    TimerManager* timerManager;
public:

    inline void createExplosion(Event* event) {
        Bomb::BombExplodeEvent* trueEvent = reinterpret_cast<Bomb::BombExplodeEvent *>(event);
        Explosion(manager, trueEvent->posX, trueEvent->posY, trueEvent->radius);
    }

    inline int initialize() override {
        GraphicScene::initialize();

        //TODO : load textures in LoadingScene...
        makeFloorTile(manager);
        makeBackground(manager, nullptr, "assets/background/test.png");
        player1 = makePlayer(manager);
        makeBorderIndestructibleWall(manager);
        Explosion(manager, 200, 200, 2);
        auto bomb = makeBomb(manager, 200, 200, 1);

        set_model_refresh_rate(400);
        set_fps(UNCAPPED);

        eventManager = EventManager::getInstance();
        timerManager= &TimerManager::getInstance();

        // On enregistre nos événements :
        eventManager->AddEventSubject(Bomb::BombExplodeEvent{}, cb::Make1(this, &GameScene::createExplosion));

        return 0;
    }

    inline int model() override {
        manager.update();

        timerManager->updateTimers();
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
                    case SDLK_SPACE:
                        eventManager->push_event(new Player::PlayerDropBombEvent{0, 5});
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
