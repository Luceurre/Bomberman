//
// Created by xdiam on 14/05/2020.
//

#ifndef ATELIERPROG_EVENTMANAGER_H
#define ATELIERPROG_EVENTMANAGER_H
#include "EventCore.h"


class EventManager {
private :
    std::map<EventType,std::vector<cb::Callback1<void,Event&>>> eventMap;

public :

    void AddEventSubject(EventType eventListened,cb::Callback1<void,Event&> funcCallback){
        eventMap[eventListened].push_back(funcCallback);
    }

    void RemoveEventSubject(EventType eventListened,cb::Callback1<void,Event&> funcCallback) {
        int i = 0;
        while(i < eventMap[eventListened].size()){
            if (eventMap[eventListened][i] == funcCallback)
                eventMap[eventListened].erase(i + eventMap[eventListened].begin());
            i++;
        }
    }


    void Dispatch(Event& eventToDispatch){
        auto x = eventMap.find(eventToDispatch.GetEventType());
        if( x != eventMap.end() ) {
            for (auto &y: x->second) {
                y(eventToDispatch);
            }
        }
    }

};


#endif //ATELIERPROG_EVENTMANAGER_H
