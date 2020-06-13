//
// Created by pglandon on 6/9/20.
//

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include <zconf.h>
#include "../Components/Components.h"
#include "../../Events/Event.h"
#include "../../Managers/EventManager.h"
#include "../../Utils/Direction.h"
#include "../../ECS/Groups/Groups.h"

#define TEX_PATH "assets/orc.png"
#define NO_ID -1


class Player : public Logger {
    inline static int playerCount = 0;
    int id;

private:
    inline static const int ANIM_WIDTH = 64;
    inline static const int ANIM_HEIGHT = 64;

    inline static const int ANIM_WALK_UP_COUNT = 9;
    inline static const int ANIM_WALK_UP_POS_X[ANIM_WALK_UP_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    inline static const int ANIM_WALK_UP_POS_Y[ANIM_WALK_UP_COUNT] = {8, 8, 8, 8, 8, 8, 8, 8, 8};
    inline static const int ANIM_WALK_UP_TICKS[ANIM_WALK_UP_COUNT] = {20, 20, 20, 20, 20, 20, 20, 20, 20};

    inline static const int ANIM_WALK_DOWN_COUNT = 9;
    inline static const int ANIM_WALK_DOWN_POS_X[ANIM_WALK_DOWN_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    inline static const int ANIM_WALK_DOWN_POS_Y[ANIM_WALK_DOWN_COUNT] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
    inline static const int ANIM_WALK_DOWN_TICKS[ANIM_WALK_DOWN_COUNT] = {20, 20, 20, 20, 20, 20, 20, 20, 20};

    inline static const int ANIM_WALK_RIGHT_COUNT = 9;
    inline static const int ANIM_WALK_RIGHT_POS_X[ANIM_WALK_RIGHT_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    inline static const int ANIM_WALK_RIGHT_POS_Y[ANIM_WALK_RIGHT_COUNT] = {11, 11, 11, 11, 11, 11, 11, 11, 11};
    inline static const int ANIM_WALK_RIGHT_TICKS[ANIM_WALK_RIGHT_COUNT] = {20, 20, 20, 20, 20, 20, 20, 20, 20};

    inline static const int ANIM_WALK_LEFT_COUNT = 9;
    inline static const int ANIM_WALK_LEFT_POS_X[ANIM_WALK_LEFT_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    inline static const int ANIM_WALK_LEFT_POS_Y[ANIM_WALK_LEFT_COUNT] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    inline static const int ANIM_WALK_LEFT_TICKS[ANIM_WALK_LEFT_COUNT] = {20, 20, 20, 20, 20, 20, 20, 20, 20};

    inline static const int ANIM_IDLE_UP_COUNT = 1;
    inline static const int ANIM_IDLE_UP_POS_X[ANIM_IDLE_UP_COUNT] = {0};
    inline static const int ANIM_IDLE_UP_POS_Y[ANIM_IDLE_UP_COUNT] = {8};
    inline static const int ANIM_IDLE_UP_TICKS[ANIM_IDLE_UP_COUNT] = {20};

    inline static const int ANIM_IDLE_DOWN_COUNT = 1;
    inline static const int ANIM_IDLE_DOWN_POS_X[ANIM_IDLE_DOWN_COUNT] = {0};
    inline static const int ANIM_IDLE_DOWN_POS_Y[ANIM_IDLE_DOWN_COUNT] = {10};
    inline static const int ANIM_IDLE_DOWN_TICKS[ANIM_IDLE_DOWN_COUNT] = {20};

    inline static const int ANIM_IDLE_RIGHT_COUNT = 1;
    inline static const int ANIM_IDLE_RIGHT_POS_X[ANIM_IDLE_RIGHT_COUNT] = {0};
    inline static const int ANIM_IDLE_RIGHT_POS_Y[ANIM_IDLE_RIGHT_COUNT] = {11};
    inline static const int ANIM_IDLE_RIGHT_TICKS[ANIM_IDLE_RIGHT_COUNT] = {20};

    inline static const int ANIM_IDLE_LEFT_COUNT = 1;
    inline static const int ANIM_IDLE_LEFT_POS_X[ANIM_IDLE_LEFT_COUNT] = {0};
    inline static const int ANIM_IDLE_LEFT_POS_Y[ANIM_IDLE_LEFT_COUNT] = {9};
    inline static const int ANIM_IDLE_LEFT_TICKS[ANIM_IDLE_LEFT_COUNT] = {20};

    inline static const int velX = 1;
    inline static const int velY = 1;

protected:
    inline string descriptor() override {
        return "(Player)";
    }

    Direction direction;
    bool walking = false;
public:
    enum PlayerState {
        IDLE_DOWN,
        IDLE_UP,
        IDLE_RIGHT,
        IDLE_LEFT,
        WALK_UP,
        WALK_DOWN,
        WALK_RIGHT,
        WALK_LEFT
    };


    inline static EventTypeManager::EventType PLAYER_MOVE = EventTypeManager::RegisterEventType();

    class PlayerEvent : public Event {
    public:
        int player_id;
    };

    class PlayerMoveEvent : public PlayerEvent {
    public:
        Direction direction;
        bool stop;

        inline PlayerMoveEvent(int id, Direction d, bool shouldStop) {
            eventType = PLAYER_MOVE;
            player_id = id;
            direction = d;
            stop = shouldStop;
        }

        inline PlayerMoveEvent() : PlayerMoveEvent(NO_ID, UP, false) {

        }
    };

    Entity* entity;
    Manager* entityManager;

    inline Player(Manager& manager) {
        id = playerCount;
        playerCount++;
        auto& e(manager.addEntity());
        entity = &e;

        vector<StatedAnimation> loadAnimations;
        
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_UP_POS_X, ANIM_IDLE_UP_POS_Y,
                                             ANIM_IDLE_UP_TICKS, ANIM_IDLE_UP_COUNT), IDLE_UP});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_DOWN_POS_X, ANIM_IDLE_DOWN_POS_Y,
                                             ANIM_IDLE_DOWN_TICKS, ANIM_IDLE_DOWN_COUNT), IDLE_DOWN});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_LEFT_POS_X, ANIM_IDLE_LEFT_POS_Y,
                                               ANIM_IDLE_LEFT_TICKS, ANIM_IDLE_LEFT_COUNT), IDLE_LEFT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_RIGHT_POS_X, ANIM_IDLE_RIGHT_POS_Y,
                                               ANIM_IDLE_RIGHT_TICKS, ANIM_IDLE_RIGHT_COUNT), IDLE_RIGHT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_RIGHT_POS_X, ANIM_WALK_RIGHT_POS_Y,
                                                ANIM_WALK_RIGHT_TICKS, ANIM_WALK_RIGHT_COUNT), WALK_RIGHT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_LEFT_POS_X, ANIM_WALK_LEFT_POS_Y,
                                                ANIM_WALK_LEFT_TICKS, ANIM_WALK_LEFT_COUNT), WALK_LEFT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_UP_POS_X, ANIM_WALK_UP_POS_Y,
                                                ANIM_WALK_UP_TICKS, ANIM_WALK_UP_COUNT), WALK_UP});
        loadAnimations.push_back({AnimationComponent(TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_DOWN_POS_X, ANIM_WALK_DOWN_POS_Y,
                                                ANIM_WALK_DOWN_TICKS, ANIM_WALK_DOWN_COUNT), WALK_DOWN});

        // Ajout des composants
        (*entity).addComponents<PositionComponent>(200, 200);
        (*entity).addComponents<MultiAnimationComponent>(loadAnimations, IDLE_DOWN);
        (*entity).addComponents<VelocityComponent>(0, 0);

        // Enregistrement des événements liés à l'entité
        auto eventManager = EventManager::getInstance();
        eventManager->AddEventSubject(PlayerMoveEvent{}, cb::Make1(this, &Player::move));

        entityManager = &manager;
    }

    inline bool canMove(int vx, int vy) {
        bool can_move = true;
        // On devrait plutot utiliser des groupes ici...
        for (auto& it : entityManager->getGroup(PLAYER_BLOCK)) {
            if (entity->hasComponent<BlockComponent>())
                info("Can I move ?");
                can_move = !entity->getComponent<BlockComponent>().handle_block(entity, vx, vy) && can_move;
        }

        return can_move;
    }

    // TODO : à améliorer pour la fluidité du jeu, but is ok
    inline void move(Event* event) {
        PlayerMoveEvent* trueEvent = reinterpret_cast<Player::PlayerMoveEvent *>(event);
        if (trueEvent->player_id == id) {
            if (trueEvent->stop) {
                // On arrête de se déplacer
                entity->getComponent<VelocityComponent>().velX = 0;
                entity->getComponent<VelocityComponent>().velY = 0;

                switch (direction) {
                    case UP:
                        entity->getComponent<MultiAnimationComponent>().setState(IDLE_UP);
                        break;
                    case DOWN:
                        entity->getComponent<MultiAnimationComponent>().setState(IDLE_DOWN);
                        break;
                    case LEFT:
                        entity->getComponent<MultiAnimationComponent>().setState(IDLE_LEFT);
                        break;
                    case RIGHT:
                        entity->getComponent<MultiAnimationComponent>().setState(IDLE_RIGHT);
                        break;
                    default:
                        break;
                }
            } else if (trueEvent->direction != direction || !walking) {
                // On check si le personnage peut bouger, les intéractions avec les autres entités sont faites ici.
                int vx = velX * DIRECTION[trueEvent->direction][0];
                int vy = velY * DIRECTION[trueEvent->direction][1];

                if (canMove(vx, vy)) {
                    entity->getComponent<VelocityComponent>().velX = vx;
                    entity->getComponent<VelocityComponent>().velY = vy;

                    direction = trueEvent->direction;
                    switch (direction) {
                        case UP:
                            entity->getComponent<MultiAnimationComponent>().setState(WALK_UP);
                            break;
                        case DOWN:
                            entity->getComponent<MultiAnimationComponent>().setState(WALK_DOWN);
                            break;
                        case LEFT:
                            entity->getComponent<MultiAnimationComponent>().setState(WALK_LEFT);
                            break;
                        case RIGHT:
                            entity->getComponent<MultiAnimationComponent>().setState(WALK_RIGHT);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
};

inline Player* makePlayer(Manager& manager) {
    auto p = new Player(manager);
    return p;
}


#endif //BOMBERMAN_PLAYER_H
