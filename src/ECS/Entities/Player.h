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
#include "Bomb.h"
#include "../../Managers/TimerManager.h"

#define NO_ID -1
#define DEFAULT_BOMB_RADIUS 2
#define DEFAULT_MAX_BOMB 3
#define DEFAULT_BOMB_RECOVERY_TICK 800 // approximativement 1 bomb/2sec
#define DEFAULT_VX 1
#define DEFAULT_VY 1
#define DEFAULT_HP 1
#define DEFAULT_INV 400

class Player : public Logger {
    inline static int playerCount = 0;
    int id;

private:
    inline static const string TEX_PATH[4] = {"assets/player1.png", "assets/player2.png", "assets/player3.png", "assets/orc.png"};

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

    inline static const int ANIM_DEAD_COUNT = 5;
    inline static const int ANIM_DEAD_POS_X[ANIM_DEAD_COUNT] = {0, 1, 2, 3, 4};
    inline static const int ANIM_DEAD_POS_Y[ANIM_DEAD_COUNT] = {20, 20, 20, 20, 20};
    inline static const int ANIM_DEAD_TICKS[ANIM_DEAD_COUNT] = {200, 200, 200, 200, 200};

    inline static const int DEFAULT_POS_X[4] = {64, 64, 704 - 128, 704 - 128};
    inline static const int DEFAULT_POS_Y[4] = {64, 704 - 128, 64, 704 - 128};

protected:
    inline string descriptor() override {
        return "(Player)";
    }

    Direction direction;
    bool walking = false;
    int bombCount;
    int maxBombCount;
    int velX;
    int velY;
    bool alive;
public:
    enum PlayerState {
        IDLE_DOWN,
        IDLE_UP,
        IDLE_RIGHT,
        IDLE_LEFT,
        WALK_UP,
        WALK_DOWN,
        WALK_RIGHT,
        WALK_LEFT,
        DEAD
    };


    inline static EventTypeManager::EventType PLAYER_MOVE = EventTypeManager::RegisterEventType();
    inline static EventTypeManager::EventType PLAYER_DROP_BOMB = EventTypeManager::RegisterEventType();
    inline static EventTypeManager::EventType PLAYER_DEATH = EventTypeManager::RegisterEventType();

    class PlayerEvent : public Event {
    public:
        int player_id;

        inline PlayerEvent(int id) {
            player_id = id;
        }

        inline PlayerEvent() {
            player_id = NO_ID;
        }
    };

    class PlayerMoveEvent : public PlayerEvent {
    public:
        Direction direction;
        bool stop;

        inline PlayerMoveEvent(int id, Direction d, bool shouldStop) : PlayerEvent(id){
            eventType = PLAYER_MOVE;
            direction = d;
            stop = shouldStop;
        }

        inline PlayerMoveEvent() : PlayerMoveEvent(NO_ID, UP, false) {

        }
    };

    class PlayerDeathEvent : public PlayerEvent {
    public:
        inline PlayerDeathEvent() : PlayerDeathEvent(NO_ID) {

        }

        inline PlayerDeathEvent(int id) : PlayerEvent(id) {
            eventType = PLAYER_DEATH;
        }
    };

    class PlayerDropBombEvent : public PlayerEvent {
    public:
        inline PlayerDropBombEvent(int id) : PlayerEvent(id) {
            eventType = PLAYER_DROP_BOMB;
        }

        inline PlayerDropBombEvent() : PlayerDropBombEvent(NO_ID) {

        }
    };

    Entity* entity;
    Manager* entityManager;
    TimerManager* timerManager;
    PositionComponent* positionComponent;
    VelocityComponent* velocityComponent;
    TrueHitboxComponent* hitboxComponent;

    inline Player(Manager& manager) {
        id = playerCount;
        playerCount++;
        auto& e(manager.addEntity(100));
        entity = &e;

        vector<StatedAnimation> loadAnimations;
        
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_UP_POS_X, ANIM_IDLE_UP_POS_Y,
                                             ANIM_IDLE_UP_TICKS, ANIM_IDLE_UP_COUNT), IDLE_UP});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_DOWN_POS_X, ANIM_IDLE_DOWN_POS_Y,
                                             ANIM_IDLE_DOWN_TICKS, ANIM_IDLE_DOWN_COUNT), IDLE_DOWN});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_LEFT_POS_X, ANIM_IDLE_LEFT_POS_Y,
                                               ANIM_IDLE_LEFT_TICKS, ANIM_IDLE_LEFT_COUNT), IDLE_LEFT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_IDLE_RIGHT_POS_X, ANIM_IDLE_RIGHT_POS_Y,
                                               ANIM_IDLE_RIGHT_TICKS, ANIM_IDLE_RIGHT_COUNT), IDLE_RIGHT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_RIGHT_POS_X, ANIM_WALK_RIGHT_POS_Y,
                                                ANIM_WALK_RIGHT_TICKS, ANIM_WALK_RIGHT_COUNT), WALK_RIGHT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_LEFT_POS_X, ANIM_WALK_LEFT_POS_Y,
                                                ANIM_WALK_LEFT_TICKS, ANIM_WALK_LEFT_COUNT), WALK_LEFT});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_UP_POS_X, ANIM_WALK_UP_POS_Y,
                                                ANIM_WALK_UP_TICKS, ANIM_WALK_UP_COUNT), WALK_UP});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_WALK_DOWN_POS_X, ANIM_WALK_DOWN_POS_Y,
                                                ANIM_WALK_DOWN_TICKS, ANIM_WALK_DOWN_COUNT), WALK_DOWN});
        loadAnimations.push_back({AnimationComponent(TEX_PATH[id], ANIM_WIDTH, ANIM_HEIGHT, ANIM_DEAD_POS_X, ANIM_DEAD_POS_Y,
                                                     ANIM_DEAD_TICKS, ANIM_DEAD_COUNT, false, cb::Make0(this, &Player::dead)), DEAD});

        // Ajout des composants
        (*entity).addComponents<PositionComponent>(DEFAULT_POS_X[id], DEFAULT_POS_Y[id]);
        (*entity).addComponents<MultiAnimationComponent>(loadAnimations, IDLE_DOWN);
        (*entity).addComponents<ConditionalVelocityComponent>(cb::Make2(this, &Player::canMove), cb::Make0(this, &Player::set_idle));
        entity->addComponents<HealPointComponent>(DEFAULT_HP, DEFAULT_INV, new PlayerDeathEvent(id));

        positionComponent = &(*entity).getComponent<PositionComponent>();
        velocityComponent = &(*entity).getComponent<ConditionalVelocityComponent>();
        hitboxComponent  = &entity->getComponent<TrueHitboxComponent>();


        // We correct player's hitbox (hard to go between walls otherwise..)
        hitboxComponent->width = 30;
        hitboxComponent->height = 50;
        hitboxComponent->shifty = 14;
        hitboxComponent->shiftx = 17;

        // Enregistrement des événements liés à l'entité
        auto eventManager = EventManager::getInstance();
        eventManager->AddEventSubject(PlayerMoveEvent{}, cb::Make1(this, &Player::move));
        eventManager->AddEventSubject(PlayerDropBombEvent{}, cb::Make1(this, &Player::dropBomb));
        eventManager->AddEventSubject(PlayerDeathEvent{}, cb::Make1(this, &Player::die));

        entityManager = &manager;
        timerManager = &TimerManager::getInstance();
        maxBombCount = DEFAULT_MAX_BOMB;
        bombRadius = DEFAULT_BOMB_RADIUS;
        bombCount = DEFAULT_MAX_BOMB;
        velX = DEFAULT_VX;
        velY = DEFAULT_VY;
        walking = false;
        alive = true;

        // On ajoute les timers lié au joueur
        timerManager->addTimer(new Timer(DEFAULT_BOMB_RECOVERY_TICK, cb::Make0(this, &Player::addBomb)));

        manager.AddToGroup(entity, PLAYER);
    }

    inline void die(Event* event) {
        PlayerDeathEvent* trueEvent = reinterpret_cast<Player::PlayerDeathEvent *>(event);
        if (trueEvent->player_id == id) {
            info("Player " + to_string(id) + " is dying...");
            alive = false;
            entity->getComponent<MultiAnimationComponent>().setState(DEAD);
        }
    }

    inline void dead() {
        info("Player " + to_string(id) + " is dead.");
        entity->active = false;
    }

    inline bool canMove(int vx, int vy) {
        if (!alive)
            return false;

        bool can_move = true;
        // On devrait plutot utiliser des groupes ici...
        for (auto& it : entityManager->getGroup(PLAYER_BLOCK)) {
            if (it->hasComponent<BlockComponent>()) {
                can_move = !it->getComponent<BlockComponent>().handle_block(entity, vx, vy) && can_move;
            }
        }

        return can_move;
    }

    inline bool addBomb() {

        if (bombCount < maxBombCount) {
            info("i'm adding bomb!");
            bombCount++;
        }
        return true;
    }

    inline void dropBomb(Event* event) {
        PlayerDropBombEvent* trueEvent = reinterpret_cast<Player::PlayerDropBombEvent *>(event);

        if (trueEvent->player_id == id) {
            // On crée une bombe au bonne endroit ici!
            if (bombCount > 0) {
                bombCount--;
                makeBomb(*entityManager, positionComponent->posX, positionComponent->posY, bombRadius);
            }
        }
    }

    inline void set_idle() {
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
    }

    // TODO : à améliorer pour la fluidité du jeu, but is ok
    inline void move(Event* event) {
        PlayerMoveEvent* trueEvent = reinterpret_cast<Player::PlayerMoveEvent *>(event);
        if (trueEvent->player_id == id) {
            if (trueEvent->stop) {
                // On arrête de se déplacer
                velocityComponent->velX = 0;
                velocityComponent->velY = 0;

                set_idle();

            } else if (trueEvent->direction != direction || !walking) {
                // On check si le personnage peut bouger, les intéractions avec les autres entités sont faites ici.
                int vx = velX * DIRECTION[trueEvent->direction][0];
                int vy = velY * DIRECTION[trueEvent->direction][1];

                if (canMove(vx, vy)) {
                    velocityComponent->velX = vx;
                    velocityComponent->velY = vy;

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

    int bombRadius;
};

inline Player* makePlayer(Manager& manager) {
    auto p = new Player(manager);
    return p;
}


#endif //BOMBERMAN_PLAYER_H
