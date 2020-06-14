//
// Created by pglandon on 6/14/20.
//

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H


#include "../Components/Components.h"

class Bomb : public Logger {
private:
    inline static const string ANIM_TEX_PATH = "assets/bomb.png";

    inline static const int ANIM_WIDTH = 64;
    inline static const int ANIM_HEIGHT = 64;

    inline static const int ANIM_COUNT = 18;
    inline static const int ANIM_POS_X[ANIM_COUNT] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2};
    inline static const int ANIM_POS_Y[ANIM_COUNT] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3};
    inline static const int ANIM_TICKS[ANIM_COUNT] = {100,100,100,100,100,100,100,100,20,20,20,20,20,20,20,20,20,20};

    inline static const EventTypeManager::EventType BOMB_EXPLODE = EventTypeManager::RegisterEventType();


protected:
    inline string descriptor() override {
        return "(Bomb)";
    }

    Manager* manager;
    Entity* entity;
    EventManager* eventManager;

    int radius;
    PositionComponent* positionComponent;
public:
    class BombExplodeEvent : public Event {
    public:
        int posX, posY, radius;

    public:
        inline BombExplodeEvent() : BombExplodeEvent(0, 0, 0) {

        }

        inline BombExplodeEvent(int x, int y, int r) {
            eventType = BOMB_EXPLODE;
            radius = r;
            posX = x;
            posY = y;
        }
    };

    inline Bomb(Manager* manager, int x, int y, int r) {
        entity = &manager->addEntity(10);
        this->manager = manager;
        eventManager = EventManager::getInstance();

        radius = r;
        entity->addComponents<PositionComponent>(x, y);
        entity->addComponents<AnimationComponent>(ANIM_TEX_PATH, ANIM_WIDTH, ANIM_HEIGHT,
                ANIM_POS_X, ANIM_POS_Y, ANIM_TICKS, ANIM_COUNT, false, cb::Make0(this, &Bomb::explode));

        positionComponent = &entity->getComponent<PositionComponent>();
    }

    inline void explode() {
        entity->active = false;
        eventManager->push_event(new BombExplodeEvent(positionComponent->posX, positionComponent->posY, radius));
    }
};

inline Bomb* makeBomb(Manager& manager, int x, int y, int r) {
    return new Bomb(&manager, x, y, r);
}

#endif //BOMBERMAN_BOMB_H
