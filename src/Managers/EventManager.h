//
// Created by pglandon on 6/8/20.
//

#ifndef BOMBERMAN_EVENTMANAGER_H
#define BOMBERMAN_EVENTMANAGER_H


#include <map>
#include <vector>
#include "../Utils/Logger.h"
#include "../Utils/Functor.h"
#include "../Events/Event.h"

// Singleton permettant la gestion d'événement.
// L'enregistrement d'événement est obligatoire pour permettre le multijoueur.
class EventManager : public Logger {
protected:
    inline std::string descriptor() override {
        return "(EventManager)";
    }

    std::map<Event, std::vector<Functor1<void, Event>>> callbackEvents;

public:
    static EventManager* getInstance()
    {
        static EventManager instance;
        return &instance;
    }

    EventManager(EventManager const&) = delete;
    void operator=(EventManager const&) = delete;


    inline EventManager() = default;

    inline void addCallback(Event e, Functor1<void, Event> callback) {
        auto it = callbackEvents.find(e);
        if (it == callbackEvents.end()) {
            callbackEvents.emplace(it, std::vector<Functor1<void, Event>>{});
        }
        callbackEvents.at(e).emplace(callback);
    }
};


#endif //BOMBERMAN_EVENTMANAGER_H
