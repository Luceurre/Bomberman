//
// Created by xdiam on 14/05/2020.
//

#ifndef ATELIERPROG_EVENTMANAGER_H
#define ATELIERPROG_EVENTMANAGER_H

#include <queue>
#include "../Events/EventCore.h"
#include "../Events/Event.h"
#include "../Utils/Logger.h"


class EventManager : protected Logger {
private :
    std::map<Event,std::vector<cb::Callback1<void,Event*>>> eventMap{};
    std::queue<Event*> eventQueue;
    std::mutex eventQueueMutex;

protected:
    inline std::string descriptor() override {
        return "(EventManager)";
    }

    inline EventManager() = default;

public :
    static EventManager* getInstance()
    {
        static EventManager instance;
        return &instance;
    }

    EventManager(EventManager const&) = delete;
    void operator=(EventManager const&) = delete;

    void AddEventSubject(const Event& eventListened,const cb::Callback1<void,Event*>& funcCallback){
        eventMap[eventListened].push_back(funcCallback);
    }

    void RemoveEventSubject(const Event& eventListened, const cb::Callback1<void,Event*>& funcCallback) {
        int i = 0;
        while(i < eventMap[eventListened].size()){
            if (eventMap[eventListened][i] == funcCallback)
                eventMap[eventListened].erase(i + eventMap[eventListened].begin());
            i++;
        }
    }


    void Dispatch(Event* eventToDispatch){
        auto x = eventMap.find(*eventToDispatch);
        if( x != eventMap.end() ) {
            for (auto &y: x->second) {
                y(eventToDispatch);
            }
        }

        delete eventToDispatch;
    }

    inline void push_event(Event* event) {
        std::lock_guard<std::mutex> lock(eventQueueMutex);
        eventQueue.push(event);
    }

    inline void dispatchQueue() {
        std::unique_lock<std::mutex> lock(eventQueueMutex);
        while (!eventQueue.empty()) {
            auto event = eventQueue.front();
            eventQueue.pop();
            lock.unlock();

            Dispatch(event);
            lock.lock();
        }
    }

    inline void handleSDL_Events() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            // Do your magic Mathis ;)
            // utilise push_event quand tu as fini de les traduire!
        }
    }
};


#endif //ATELIERPROG_EVENTMANAGER_H
