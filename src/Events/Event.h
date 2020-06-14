//
// Created by xdiam on 13/05/2020.
//

#ifndef ATELIERPROG_EVENT_H
#define ATELIERPROG_EVENT_H

#include "EventCore.h"

#include <SDL_Event.h>

class EventTypeManager
{
public:
    typedef int EventType;

    inline static EventType cursor = 0;

    inline static EventType NextEventType() {return cursor + 1;}

    inline static EventType RegisterEventType()
    {
        cursor = NextEventType();
        return cursor;
    };

    inline static EventType   None                = 0,
                WindowClose         = RegisterEventType(),
                WindowResize        = RegisterEventType(),
                WindowFocus         = RegisterEventType(),
                WindowLostFocus     = RegisterEventType(),
                WindowMoved         = RegisterEventType(),
                AppTick             = RegisterEventType(),
                AppUpdate           = RegisterEventType(),
                AppRender           = RegisterEventType(),
                KeyPressed          = RegisterEventType(),
                KeyReleased         = RegisterEventType(),
                KeyTyped            = RegisterEventType(),
                MouseButtonPressed  = RegisterEventType(),
                MouseButtonReleased = RegisterEventType(),
                MouseMoved          = RegisterEventType(),
                MouseScrolled       = RegisterEventType();
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication    = BIT(0),
    EventCategoryInput          = BIT(1),
    EventCategoryKeyboard       = BIT(2),
    EventCategoryMouse          = BIT(3),
    EventCategoryMouseButton    = BIT(4)
};

// We use struct instead of class because we have to pass it around the network
// and this has a greater chance of sucess.
class Event {
public:
    EventTypeManager::EventType eventType = EventTypeManager::None;

    inline virtual bool isPoly() {
        return true;
    }

    inline friend bool operator==(Event l, Event r) {
        return l.eventType == r.eventType;
    }

    inline friend bool operator<(Event l, Event r) {
        return l.eventType < r.eventType;
    }

    inline EventTypeManager::EventType GetEventType() {
        return eventType;
    }
};

class SDLEvent : public Event {
public:
    SDL_Event event;

    inline static EventTypeManager::EventType SDLEventType = EventTypeManager::RegisterEventType();

    inline SDLEvent(SDL_Event e) {
        eventType = SDLEventType;
        event = e;
    }

    inline friend bool operator==(SDLEvent l, SDLEvent r) {
        return l.event.type == r.event.type;
    }
};



#define KEY_PRESSED_EVENT(key,sender)   Event key_pressed_##key\
                                        key_pressed_##key.senderIdentity    = sender\
                                        key_pressed_##key.intData           = key\
                                        key_pressed_##key.type              = KeyPressed\
                                        key_pressed_##key.category          = EventCategoryKeyboard | EventCategoryInput



#endif //ATELIERPROG_EVENT_H
