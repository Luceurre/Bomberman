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
    Player* player2;
    Player* player3;
    TimerManager* timerManager;
    int playerCount;
    int playerAlive;
    std::vector<int> playerScore;
public:

    inline GameScene(int nbJoueur = 2) : GraphicScene() {
        playerCount = nbJoueur;
        playerAlive = nbJoueur;
    }

    inline void createExplosion(Event* event) {
        Bomb::BombExplodeEvent* trueEvent = reinterpret_cast<Bomb::BombExplodeEvent *>(event);
        Explosion(manager, trueEvent->posX, trueEvent->posY, trueEvent->radius);
    }

    inline int initialize() override {
        GraphicScene::initialize();

        //TODO : load textures in LoadingScene...
        makeFloorTile(manager);

        for(int i = 0; i < playerCount; i++)
            makePlayer(manager);
        makeBorderIndestructibleWall(manager);

        set_model_refresh_rate(400);
        set_fps(UNCAPPED);

        eventManager = EventManager::getInstance();
        timerManager= &TimerManager::getInstance();

        // On enregistre nos événements :
        eventManager->AddEventSubject(Bomb::BombExplodeEvent{}, cb::Make1(this, &GameScene::createExplosion));
        eventManager->AddEventSubject(Player::PlayerDeathEvent{}, cb::Make1(this, &GameScene::end));

        return 0;
    }

    inline void end(Event* event) {
        Player::PlayerEvent* trueEvent = reinterpret_cast<Player::PlayerEvent *>(event);
        playerAlive--;
        playerScore.push_back(trueEvent->player_id);

        if (playerAlive <= 1)
            exit(0);
    }

    inline int controller() override {
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
                        eventManager->push_event(new Player::PlayerDropBombEvent{0});
                        break;
                    case SDLK_UP:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, UP, false});
                        break;
                    case SDLK_DOWN:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, DOWN, false});
                        break;
                    case SDLK_LEFT:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, LEFT, false});
                        break;
                    case SDLK_RIGHT:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, RIGHT, false});
                        break;
                    case SDLK_RCTRL:
                        eventManager->push_event(new Player::PlayerDropBombEvent{1});
                        break;
                    case SDLK_KP_8:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, UP, false});
                        break;
                    case SDLK_KP_5:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, DOWN, false});
                        break;
                    case SDLK_KP_4:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, LEFT, false});
                        break;
                    case SDLK_KP_6:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, RIGHT, false});
                        break;
                    case SDLK_KP_ENTER:
                        eventManager->push_event(new Player::PlayerDropBombEvent{2});
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
                    case SDLK_UP:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, UP, true});
                        break;
                    case SDLK_DOWN:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, DOWN, true});
                        break;
                    case SDLK_LEFT:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, LEFT, true});
                        break;
                    case SDLK_RIGHT:
                        eventManager->push_event(new Player::PlayerMoveEvent{1, RIGHT, true});
                        break;
                    case SDLK_KP_8:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, UP, true});
                        break;
                    case SDLK_KP_5:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, DOWN, true});
                        break;
                    case SDLK_KP_4:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, LEFT, true});
                        break;
                    case SDLK_KP_6:
                        eventManager->push_event(new Player::PlayerMoveEvent{2, RIGHT, true});
                        break;
                    default:
                        break;
                }
            }

            eventManager->push_event(eventSDL);
        }
    }

    inline int model() override {
        manager.update();

        timerManager->updateTimers();
        eventManager->dispatchQueue();

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
